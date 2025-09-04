#include <iostream>
#include "../Log.h"
#include "../ConsoleRenderer.h"
#include <tgmath.h>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <thread>
#include <vector>

#define CHRONO_CLOCK std::chrono::system_clock
#define CHRONO_DURATION std::chrono::duration

#define LOG(txt) std::cout << txt << std::endl;

#pragma region Herança com structs

class Class_a
{
public:
	Class_a() { redundancia = 0; }
	int redundancia;
};

struct Struct_b : Class_a
{
	void Log()
	{
		std::cout << *&redundancia << std::endl;
	}
};

#pragma endregion


class MainLoop
{
	float dt = 0;
	float target_dt = 0.016;
	CHRONO_CLOCK::time_point then;

public:
	void SetTargetDT(float value)
	{
		target_dt = value;
	}

	float DeltaTime()
	{
		return dt;
	}

	bool Tick()
	{
		CHRONO_DURATION<double> dif;
		dif = CHRONO_CLOCK::now() - then;
		dt = dif.count();

		if (dt >= target_dt)
		{
			then = CHRONO_CLOCK::now();
			return true;
		}
		else
		{
			return false;
		}
	}
};

#define OSTREAM std::ostream
class Vertex {
public:
	float x, y, z;

	Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

	// Função de copia. Ver CONVERSÃO IMPLICITA
	Vertex(const Vertex& vertex) : x(vertex.x), y(vertex.y), z(vertex.z)
	{
		std::cout << "Vertex copied!" << std::endl;
	}

	friend OSTREAM& operator<<(OSTREAM& os, const Vertex& dt);
};

OSTREAM& operator<<(OSTREAM& os, const Vertex& dt) // OSTREAM& referencia para OSTREAM
{
	return os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ") ";
}



struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		LOG(duration.count() * 1000.0f);
	}
};

// Um objeto timer é criado no inicio da funçao, momento onde o tempo inicial é salvo.
// no fim da função, timer sai do escopo então seu destrutor é chamado e o tempo gasto exibido.
void FunctionTimmed()
{
	Timer timer;

	std::cout << "Done!" << std::endl;
}


int main()
{
	struct Test
	{
		float x, y, z;
	};

	//Test* offset1 = (Test*)0; // var = null ou 0x000000...
	//Test* offset2 = (Test*)nullptr; // var = null ou 0x000000... mesmo que Test* var = nullptr;
	//float offset3 = ((Test*)nullptr)->x; // excption, acessando endereço invalido
	//float* offset4 = &((Test*)nullptr)->x; // 0x000000... <Unable to read memory>
	int offset5 = (int)&((Test*)nullptr)->z; // posição em bytes de z.

	//==================== PONTEIROS
	// - Copiar um classe onde um dos parametros é um ponteiro, o ponteiro(endereço de memoria) será copiado
	// podendo gerar bugs como por exemplo mudar o valor apontado em um objeto tambem muda o do outro ja q são
	// o mesmo. Pare evitar problemas pode se criar um "construtor de copia" do tipo Type(const Type& other) e para
	// proibir copias algo como Type(const Type& other) = delete;
	std::cout << std::endl << "==================== POINTERS" << std::endl;
	
	// Alocando um array de characteres
	char* buffer = new char[8];
	memset(buffer, 0, 8);
	
	// Alocando um inteiro
	int b;
	memset(&b, 0, sizeof(int)); // inicializando b com 0 hard mode
	int* b_ptr = &b;

	// Peripercias com aritimetica de ponteiros
	int a = 10;
	int* aptr = &a;
	*aptr = (int) & aptr;

	std::cout << aptr << std::endl;
	std::cout << aptr[0] << std::endl;

	std::cout << aptr + 1 << std::endl; // Avança um posição na memoria de acordo com o tipo. Int avança 4 bytes.
	std::cout << aptr[1] << std::endl;

	std::cout << aptr[3] << std::endl;
	std::cout << *(aptr + 3) << std::endl;
	std::cout << aptr + 3 << std::endl;
	std::cout << &aptr[3] << std::endl;
	

	//==================== ARRAYS
	std::cout << std::endl << "==================== ARRAYS" << std::endl;
	int vet[4] = {1, 2, 3, 21};
	int* vet_ptr = vet; //vet puro é o endereço do primeiro elemento do vetor.
	void* ponteiroParaPos3DoArray = &vet[3];
	std::cout << vet << std::endl;

	// não pode mudar caracteres
	const char* constantString = "Hello";
	std::cout << constantString << std::endl;

	// cou << mutableString2 irá printar Hello + lixo de memoria até encontrar o ponto de parada.
	char mutableString2[] = {'H', 'e', 'l', 'l', 'o'};
	//std::cout << mutableString2 << std::endl;
	
	// imprime Hello normalmente.
	char mutableString3[] = { 'H', 'e', 'l', 'l', 'o', '\0'};
	std::cout << mutableString3 << std::endl;
	char mutableString4[] = { 'H', 'e', 'l', 'l', 'o', 0};
	std::cout << mutableString4 << std::endl;
	char mutableString5[] = { 'H', 'e', 'l', 'l', 'o', NULL};
	std::cout << mutableString5 << std::endl;
	char mutableString[] = "Hello";
	std::cout << mutableString << std::endl;

	Class_a ca;
	// n compila Struct_b sb = (Struct_b)ca;
	//Struct_b sb = Struct_b();
	Struct_b sb;
	sb.Log();
	ca = (Class_a)sb;

	// ==================== VECTORS
	std::cout << std::endl << "==================== VECTORS" << std::endl;


	// Aqui o vector ira mudar seu tamanho a cada novo set de elementos adicionado
	// fazendo com que a operação de copia de Vertex seja executada 6 vezes ao inves de 3.
	std::vector<Vertex> vertices;

	// Iso pode ser resolvido usando reserve. OTIMIZAÇÃO
	vertices.reserve(3);

	//vertices.push_back(Vertex(1, 2, 3)); // Add
	//vertices.push_back(Vertex(4, 5, 6));
	//vertices.push_back(Vertex(7, 8, 9)); // vertices.push_back({7, 8, 9});
	
	// Entretanto é possivel não fazer nenhuma copia e criar os Vertex diretamente no vector
	// utilizando emplace_back. Mas reserve continua sendo nescessario! iSSO EVITA QUALQUER COPIAS,
	// QUE SEMPRE SÃO FEITAS USANDO PUSH_BACK.
	vertices.emplace_back(1, 2, 3);
	vertices.emplace_back(4, 5, 6);
	vertices.emplace_back(7, 8, 9);

	for (Vertex& v : vertices) // Assim (sem ref &) vai fazer copias do vertex: for (Vertex v : vertices)
	{
		std::cout << v;
	}

	// ================================ STATIC
	// static é relativo a um escopo. se  uma variavel é declarada comop static dentro de um função é como
	// se tivesse sido declarado fora, é compartilhada e cada vez q função for chamada é a mesma variavel que será usada.
	// Mesmo em uma classe onde todas as instancias da classe compartilham a variavel.

	// ==================== TIMING
	std::cout << std::endl << "==================== TIMING" << std::endl;
	FunctionTimmed();
	


	//====================== LOG
	std::cout << std::endl << "==================== LOG" << std::endl;
	Log log;
	log.Error("Hello!");
	log.Warning("Hello!");
	log.Info("Hello!");
	std::cin.get();

	//==================== LOOP
	std::cout << std::endl << "==================== LOOP" << std::endl;
	MainLoop mainLoop;
	mainLoop.SetTargetDT(0.00016);
	ConsoleRenderer renderer(200, 100);

	float fc = 0;
	while (true)
	{
		if (mainLoop.Tick())
		{
			//renderer.Draw(mainLoop.DeltaTime());
			renderer.Draw(0.016);
			std::cout << std::endl << mainLoop.DeltaTime();
			//fc += mainLoop.DeltaTime();
			//if (fc >= 5) break;
		}
		else
		{
			continue;
		}
	}

	std::cin.get();


	class WhichAreIn
	{

	public:
		static std::vector<std::string> inArray(std::vector<std::string>& array1, std::vector<std::string>& array2)
		{
			std::vector<std::string> subStrings;
			// Avoid return vector to resize when adding new elements by alocating space to maximun possible elements.
			subStrings.reserve(array1.size());

			for (int ar1_i = 0; ar1_i < array1.size(); ar1_i++)
			{
				for (int ar2_j = 0; ar2_j < array2.size(); ar2_j++)
				{
					if (array2[ar2_j].find(array1[ar1_i]) != std::string::npos)
					{
						auto it = std::upper_bound(subStrings.begin(), subStrings.end(), array1[ar1_i]);
						subStrings.insert(it, array1[ar1_i]);
					}
				}
			}

			return subStrings;
		}
	};

	
}