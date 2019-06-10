#include "Reptil.h"

Reptil::Reptil(){

}
Reptil::Reptil(int id, string classe, string nome_cientifico, char sexo, 
			double tamanho, string dieta, Veterinario* veterinario, 
			Tratador* tratador, string nome_batismo, bool venenoso,
			string tipo_veneno):
	Animal(id, classe, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, nome_batismo),
	m_venenoso(venenoso), m_tipo_veneno(tipo_veneno){

}
Reptil::~Reptil(){

}

void Reptil::set_venenoso(bool venenoso){
	m_venenoso = venenoso;
}
void Reptil::set_tipo_veneno(string tipo_veneno){
	m_tipo_veneno = tipo_veneno;
}
bool Reptil::get_venenoso(){
	return m_venenoso;
}
string Reptil::get_tipo_veneno(){
	return m_tipo_veneno;
}

string Reptil::write(){
	ostringstream str;
	str<<m_id<<";";
	str<<m_classe<<";";
	str<<m_nome_cientifico<<";";
	str<<m_sexo<<";";
	str<<m_tamanho<<";";
	str<<m_dieta<<";";
	str<<m_veterinario->get_id()<<";";
	str<<m_tratador->get_id()<<";";
	str<<m_nome_batismo<<";";
	str<<m_venenoso<<";";
	str<<m_tipo_veneno<<endl;

	return str.str();
};

string Reptil::Tipo(){
	return "Reptil";
};

ostream& Reptil::print(ostream& os)const{
	os<<"Campo \tTipo de Dados \tValores"<<endl;
	os<<"Identificador Do animal \tInteiro \t"<<m_id<<endl;
	os<<"Classe do animal \tCadeia de caracteres \t"<<m_classe<<endl;
	os<<"Nome científico do animal \tCadeia de caracteres \t"<<m_nome_cientifico<<endl;
	os<<"Sexo do animal \tCaractere \t"<<m_sexo<<endl;
	os<<"Tamanho média em métros \tDecimal \t"<<m_tamanho<<endl;
	os<<"Dieta redominante \tCadeia de caracteres \t"<<m_dieta<<endl;
	os<<"Veterinário associado \tInterio \t"<<m_veterinario->get_id()<<endl;
	os<<"Tratador responsável \tInterio \t"<<m_tratador->get_id()<<endl;
	os<<"Nome de batismo \tCadeia de caracteres \t"<<m_nome_batismo<<endl;
	os<<"Venenoso \tbooleano \t"<<m_venenoso<<endl;
	os<<"Tipo de veneno \tCadeia de caracteres \t"<<m_tipo_veneno<<endl;
	
	return os;
}