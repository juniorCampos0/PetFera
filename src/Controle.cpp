#include "Controle.h"

using namespace std;

Controle::Controle(){
	ifstream arch;
	string line;

	arch.open("config/config.txt");
	if(!(arch.is_open())){
		cerr<<"O arquivo de configuração não foi aberto!!!"<<endl;
	}

	getline(arch, line);
	id = stoi(line);
	arch.close();

	ifstream archive;

	//Leitura dos Funcionários
	archive.open("data/Funcionarios.csv");
	if(!(archive.is_open())){
		cerr<<"O arquivo de funcionários não foi aberto!!!"<<endl;
		return;
	}
	//getline(archive, line);
	shared_ptr<Funcionario> funcionario;

	while(getline(archive, line)){
		funcionario = tratamento.Tratamento_Construtor_Funcionario(line);
		if(funcionario != NULL)
			funcionarios_m[funcionario->get_id()] = funcionario;
	}
	archive.close();

	//Leitura dos Animais
	archive.open("data/Animais.csv");
	if(!(archive.is_open())){
		cerr<<"O arquivo de animais não foi aberto!!!"<<endl;
		return;
	}
	//getline(archive, line);
	shared_ptr<Animal> bicho;

	while(getline(archive, line)){
		bicho = tratamento.Tratamento_Construtor_Animal(line, funcionarios_m);
		if(bicho != NULL)
			animais_m[bicho->get_m_id()] = bicho;
	}
	archive.close();
};

int Controle::definir_id(){
	id += 1;
	return this->id;
}

Controle::Controle(map<int, Animal>, map<int, Funcionario>){}

Controle::~Controle(){
	system("rm -rf config/config.txt");
	system("touch config/config.txt");

	ofstream arq("config/config.txt", ios::app | ios::binary);

	if(arq.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}
	ostringstream str;
	str<<id;
	arq<<str.str();
	arq.close();
	
	system("rm -rf data/Animais.csv");
	system("touch data/Animais.csv");

	ofstream arq_1("data/Animais.csv", ios::app | ios::binary);
	if(arq_1.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}

	for(auto it = animais_m.begin(); it != animais_m.end(); it++){
		arq_1<< it->second->write();
	}

	arq_1.close();

	system("rm -rf data/Funcionarios.csv");
	system("touch data/Funcionarios.csv");

	ofstream arch("data/Funcionarios.csv", ios::app | ios::binary);
	if(arch.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}

	for(auto it = funcionarios_m.begin(); it != funcionarios_m.end(); it++){
		arch<< it->second->write();
	}
	arch.close();
}

// Métodos privados para validar tipos
void Controle::definir_responsavel(shared_ptr<Animal> &bicho, string funcao){
	cout << "Digite o id do "<<funcao<<": " << endl;
	char *valor = new char;
	cin.clear();
	cin.getline(valor, 50);
	int id = is_number(valor);

	auto it = funcionarios_m.find(id);
	while(it == funcionarios_m.end() or it->second->Tipo().compare(funcao) ){
		cout<< funcao <<"não encontrado!"<<endl;
		cout<<"Digite o id novamente: ";
		cin.clear();
		cin.getline(valor, 50);
		id = is_number(valor);
		it = funcionarios_m.find(id);
	}

	if( !funcao.compare("Veterinario") ){
		shared_ptr<Veterinario> f = dynamic_pointer_cast<Veterinario>(it->second);
		bicho->set_m_veterinario(f);
	}
	else if( !funcao.compare("Tratador") ){
		shared_ptr<Tratador> f = dynamic_pointer_cast<Tratador>(it->second);
		bicho->set_m_tratador(f);
	}
	delete valor;
};

int Controle::is_number(char * number){
	int i = 0;
	while(number[i] != '\0'){
		if ((number[i] < 48 || number[i] > 57)){

			i = 0;
			cout << "Isso não é um número, tente novamente: " << endl;
			cin.clear();
			cin.getline(number,20);
		}
		i++;
	}
	return stoi(number);
};



void Controle::adicionar_animal(){
	TratamentoInput input;
	if (!(funcionario_valido())){
		return;
	}

	int option_1;
	int option_2;
	cout << "Digite a opção desejada: " << endl;
	cout << "\t 1 - Anfibio;" << endl;
	cout << "\t 2 - Ave;" << endl;
	cout << "\t 3 - Mamifero;" << endl;
	cout << "\t 4 - Reptil;" << endl;
	cout << "\t 5 - Peixe;" << endl;
	cout << "\t 6 - Inseto;" << endl;
	cout << "\t 7 - Aracnideo;" << endl;

	option_1 = input.inputInt();

	while(option_1 < 1 || option_1 > 8){
		cout << "Esse número não é valido, tente novamente: " << endl;
		option_1 = input.inputInt();
	}

	cout << "Digite o tipo correspondente: " << endl;
	cout << "\t 1 - Domestico;" << endl;
	cout << "\t 2 - Silvestre Exotico;" << endl;
	cout << "\t 3 - Silvestre Nativo;" << endl; 

	option_2 = input.inputInt();

	while(option_2 < 1 || option_2 > 3){
		cout << "Esse número não é valido, tente novamente: " << endl;
		option_2 = input.inputInt();
	}

	if (option_1 == 1){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new AnfibioDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new AnfibioExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new AnfibioNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 2){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new AveDomestica);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new AveExotica);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new AveNativa);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 3){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new MamiferoDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new MamiferoExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new MamiferoNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 4){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new ReptilDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new ReptilExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new ReptilNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 5){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new PeixeDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new PeixeExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new PeixeNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 6){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new InsetoDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new InsetoExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new InsetoNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}
	else if (option_1 == 7){
		if(option_2 == 1){
			shared_ptr<Animal> bicho(new AracnideoDomestico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 2){
			shared_ptr<Animal> bicho(new AracnideoExotico);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
		if(option_2 == 3){
			shared_ptr<Animal> bicho(new AracnideoNativo);
			bicho->inicializar_animal(definir_id());
			definir_responsavel(bicho, "Veterinario");
			definir_responsavel(bicho, "Tratador");
			animais_m[bicho->get_m_id()] = bicho;
		}
	}

	// ofstream arq("data/Animais.csv", ios::app | ios::binary);
	// if(arq.bad()){
	// 	cerr<<"Arquivo nao foi aberto"<<endl;
	// 	exit(1);
	// }
	// arq<<animais_m[]->write();
	// arq.close();
}

void Controle::remover_animal(){
	TratamentoInput input;
	cout << "\nDigite o id do animal que deseja remover: " << endl;
	int option;
	option = input.inputInt();
	if ((int)animais_m.count(option) > 0){
		animais_m.erase(option);
		cout << "Animal Excluído." << endl;
	}
	else{
		cout << "Não existe animal com esse id." << endl;
	}
}

void Controle::alterar_animal(){
	TratamentoInput input;
	string atributo;

	cout<< "Digite o id do animal a ser alterado: ";
	int id_a = input.inputInt();

	auto it = animais_m.find(id_a);
	while(it == animais_m.end()){
		cout<< "Animais não encontrado!" <<endl;
		cout<<"Digite o id novamente: ";
		id_a = input.inputInt();
		it = animais_m.find(id_a);
	}
	cout<<endl;
	cout<<"Digite o atributo a ser alterado:"<<endl;
	cout<<"-nome cientifico"<<endl;
	cout<<"-sexo"<<endl;
	cout<<"-veterinario"<<endl;
	cout<<"-tratador"<<endl;
	cout<<"-tamanho do animal"<<endl;
	cout<<"-dieta"<<endl;
	cout<<"-nome de batismo"<<endl;
	string tipo = it->second->Tipo();

	if(!tipo.compare("AnfibioDomestico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
	}
	else if(!tipo.compare("AnfibioNativo")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("AnfibioExotico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("AveDomestica")){
		cout<<"-tamanho do bico"<<endl;
		cout<<"-envergadura das asas"<<endl;
	}
	else if(!tipo.compare("AveNativa")){
		cout<<"-tamanho do bico"<<endl;
		cout<<"-envergadura das asas"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("AveExotica")){
		cout<<"-tamanho do bico"<<endl;
		cout<<"-envergadura das asas"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("AracnideoDomestico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de veneno"<<endl;
	}
	else if(!tipo.compare("AracnideoNativo")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de veneno"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("AracnideoExotico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de veneno"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("InsetoDomestico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de metamorfose"<<endl;
	}
	else if(!tipo.compare("InsetoNativo")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de metamorfose"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("InsetoExotico")){
		cout<<"-total de mudas"<<endl;
		cout<<"-data da última muda (data)"<<endl;
		cout<<"-tipo de metamorfose"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("MamiferoDomestico")){
		cout<<"-cor do pelo"<<endl;
	}
	else if(!tipo.compare("MamiferoNativo")){
		cout<<"-cor do pelo"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("MamiferoExotico")){
		cout<<"-cor do pelo"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("PeixeDomestico")){
		cout<<"-tipo de agua"<<endl;
	}
	else if(!tipo.compare("PeixeNativo")){
		cout<<"-tipo de agua"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("PeixeExotico")){
		cout<<"-tipo de agua"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	else if(!tipo.compare("ReptilDomestico")){
		cout<<"-venenoso"<<endl;
		cout<<"-tipo de veneno"<<endl;
	}
	else if(!tipo.compare("ReptilNativo")){
		cout<<"-venenoso"<<endl;
		cout<<"-tipo de veneno"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-uf de origem"<<endl;
	}
	else if(!tipo.compare("ReptilExotico")){
		cout<<"-venenoso"<<endl;
		cout<<"-tipo de veneno"<<endl;
		cout<<"-autorização do Ibama (ibama)"<<endl;
		cout<<"-pais de origem"<<endl;
		cout<<"-cidade de origem"<<endl;
	}
	atributo = input.inputString();

	if(!atributo.compare("veterinario")){
		definir_responsavel(it->second, "Veterinario");
	}
	else if(!atributo.compare("tratador")){
		definir_responsavel(it->second, "Tratador");
	}
	else
		it->second->alterar_animal(atributo);
}

void Controle::consultar_animais(){
	char* valor = new char;
	int option;
	int id;
	cout << "Digite a opção desejada: " << endl;
	cout << "\t 1 - Consultar todos os animais;" << endl;
	cout << "\t 2 - Consultar animal por id;" << endl;

	cin.clear();
	cin.getline(valor,20);
	option = is_number(valor);

	while(option < 1 || option > 2){
		cout << "Esse opção não é valida, tente novamente: " << endl;
		cin.clear();
		cin.getline(valor,20);
		option = is_number(valor);
	}

	if(option == 1){
		for(auto it = animais_m.begin(); it != animais_m.end(); it++)
			cout<< *it->second << endl << endl;
	}
	else if(option == 2){
		cout << "Digite o id do animal: " << endl;
		cin.clear();
		cin.getline(valor, 50);
		id = is_number(valor);

		auto it = animais_m.find(id);
		if(it == animais_m.end())
			cout<<"Animal não encontrado"<<endl << endl; 
		else
			cout << *it->second << endl << endl;
	}
}

void Controle::consultar_animais_por_funcionario(){

}
		
void Controle::adicionar_funcionario(){
	int option_1;
	TratamentoInput input;

	cout << "Digite a opção desejada: " << endl;
	cout << "\t1 - Adicionar tratador" << endl;
	cout << "\t2 - Adicionar veterinário" << endl;

	option_1 = input.inputInt();

	while(option_1 < 1 || option_1 > 2){
		cout << "Esse número não é valido, tente novamente: " << endl;
		option_1 = input.inputInt();
	}

	if(option_1 == 1){
		shared_ptr<Funcionario> funcionario(new Tratador);
		funcionario->inicializar_funcionario(definir_id());
		funcionarios_m[funcionario->get_id()] = funcionario;
	}
	else if(option_1 == 2){
		shared_ptr<Funcionario> funcionario(new Veterinario);
		funcionario->inicializar_funcionario(definir_id());
		funcionarios_m[funcionario->get_id()] = funcionario;
	}
}

void Controle::remover_funcionario(){
	TratamentoInput input;
	cout << "\nDigite o id do funcionário que deseja remover: " << endl;
	int option;
	option = input.inputInt();
	if ((int)funcionarios_m.count(option) > 0){
		if ((int)funcionarios_m[option].use_count() > 1){
			cout << "\t Não é possíve remover esse funcionário, existem animais ligados ele." << endl;
			cout << "\t Para remover o funcionário altere todos os animais associados a ele." << endl;
		}
		else{
			funcionarios_m.erase(option);
			cout << "Funcionário removido com sucesso." <<  endl;
		}
	}
	else{
		cout << "Não existe funcionario com esse id." << endl;
	}
}

void Controle::alterar_funcionario(){
	TratamentoInput input;

	cout<< "Digite o id do funcionário a ser alterado: ";
	int id_f = input.inputInt();

	auto it = funcionarios_m.find(id_f);
	while(it == funcionarios_m.end()){
		cout<< "Funcionário não encontrado!" <<endl;
		cout<<"Digite o id novamente: ";
		id_f = input.inputInt();
		it = funcionarios_m.find(id_f);
	}
	cout<<endl;
	it->second->alterar_funcionario();
}

void Controle::salvar_alteracoes(){
	system("rm -rf config/config.txt");
	system("touch config/config.txt");

	ofstream arq_("config/config.txt", ios::app | ios::binary);

	if(arq_.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}
	ostringstream str;
	str<<id;
	arq_<<str.str();
	arq_.close();

	cout << "Salvando alterações nos animais." << endl;
	system("rm -rf data/Animais.csv");
	system("touch data/Animais.csv");

	ofstream arq("data/Animais.csv", ios::app | ios::binary);
	if(arq.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}

	for(auto it = animais_m.begin(); it != animais_m.end(); it++){
		arq << it->second->write();
	}

	arq.close();

	cout << "Alterações salvas com sucesso." << endl;

	cout << "Salvando alterações nos funcionários." << endl;

	system("rm -rf data/Funcionarios.csv");
	system("touch data/Funcionarios.csv");

	ofstream arch("data/Funcionarios.csv", ios::app | ios::binary);
	if(arch.bad()){
		cerr<<"Arquivo nao foi aberto"<<endl;
		exit(1);
	}

	for(auto it = funcionarios_m.begin(); it != funcionarios_m.end(); it++){
		arch << it->second->write();
	}
	arch.close();

	cout << "Alterações salvas com sucesso." << endl;
}

void Controle::consultar_funcionario(){
	char* valor = new char;
	int option;
	int id;
	cout << "Digite a opção desejada: " << endl;
	cout << "\t 1 - Consultar todos os funcionários;" << endl;
	cout << "\t 2 - Consultar funcionário por id;" << endl;

	cin.clear();
	cin.getline(valor,20);
	option = is_number(valor);

	while(option < 1 || option > 2){
		cout << "Esse opção não é valida, tente novamente: " << endl;
		cin.clear();
		cin.getline(valor,20);
		option = is_number(valor);
	}

	if(option == 1){
		for(auto it = funcionarios_m.begin(); it != funcionarios_m.end(); it++)
			cout<< *it->second << endl << endl;
	}
	else if(option == 2){
		cout << "Digite o id do funcionario: " << endl;
		cin.clear();
		cin.getline(valor, 50);
		id = is_number(valor);

		auto it = funcionarios_m.find(id);
		if(it == funcionarios_m.end())
			cout<<"Funcionário não encontrado"<<endl << endl;
		else
			cout << *it->second << endl << endl;
	}

	delete[] valor;
}

bool Controle::funcionario_valido(){
	bool Trat = false;
	bool Vet = false;

	for(auto it = funcionarios_m.begin(); it != funcionarios_m.end(); it++){
		if (it->second->Tipo() == "Tratador"){
			Trat = true;
		};
		if (it->second->Tipo() == "Veterinario"){
			Vet = true;
		}
	}

	if(!(Trat)){
		cout << "\t Necessário adicionar um tratador." << endl;
	}
	if(!(Vet)){
		cout << "\t Necessário adicionar um veterinário." << endl;
	}

	return (Trat and Vet);
};