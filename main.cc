#include <cstddef>

#include <string>
#include <iostream>
#include <fstream>

#include <array>
#include <vector>
#include <list>

class Program
{
protected:

  class Data
  {
  public:

    /* Disk data initialization process */

    Data ()
    {
      if (!load_data())
        std::cerr << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido para leitura." << std::endl;
    }

    ~ Data ()
    {
      if (!update_data())
        std::cerr << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido para escrita." << std::endl;
    }


    /* Data structs */

    struct Pergunta
    {
      std::string enunciado;
      std::array<std::string, 4> questoes;
      char resposta;
    };

    struct Jogador
    {
      std::string nome;
      size_t pontuacao;
    };

    /* Data storage */

    std::vector<Pergunta> perguntas;
    std::list<Jogador> ranking;

    /* Disk data manipulation functions */
    
    signed load_data (void)
    {
      /* Disk data loading */

      // Reading the questions

      std::ifstream perguntas_txt ("perguntas.txt");
      if (!perguntas_txt.is_open()) return -1;

      std::string stmp;

      while (true)
      {
        Pergunta p;

        if (!std::getline(perguntas_txt, stmp)) return 1;
        p.enunciado.assign(stmp);

        for (std::string& s : p.questoes)
        {
          if (!std::getline(perguntas_txt, stmp)) return 1;
          s.assign(stmp);
        }

        std::getline(perguntas_txt, stmp);
        p.resposta = stmp[0] - 'A';
        
        perguntas.push_back(p);

        if (perguntas_txt.eof()) break;

        if (!std::getline(perguntas_txt, stmp)) return 1;
      }

      perguntas_txt.close();

      // Reading the ranking

      std::ifstream ranking_txt ("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      while (!ranking_txt.eof())
      {
        Jogador j;

        ranking_txt >> j.nome >> j.pontuacao;

        ranking.push_back(j);
      }
      
      ranking_txt.close();

      return 0;
    }

    signed update_data (void)
    {
      /* Disk data updating */

      // Writing the questions

      std::ofstream perguntas_txt ("perguntas.txt");
      if (!perguntas_txt.is_open()) return -1;

      for (const Pergunta& p : perguntas)
      {
        if (!(perguntas_txt << p.enunciado << std::endl)) return 1;

        for (const std::string& s : p.questoes)
          if (!(perguntas_txt << s << std::endl)) return 1;

        if (!(perguntas_txt << p.resposta << std::endl << std::endl)) return 1;
      }

      perguntas_txt.close();
      
      // Writing the ranking

      std::ofstream ranking_txt ("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      for (Jogador& j : ranking)
        if (!(perguntas_txt << j.nome << j.pontuacao)) return 1;
      
      ranking_txt.close();

      return 0;
    };

  } data;

  class UserInterface
  {
  protected:
    
    size_t points;

  public:

    signed perguntar (const size_t& i, const Data::Pergunta& p)
    { 
      /* Show question interface for question `i` */

      char ans;

      std::cout << "Pergunta " << i << ':' << std::endl ;

      std::cout << p.enunciado << std::endl << std::endl;

      for (const std::string& s : p.questoes)
        std::cout << s << std::endl;

      std::cout << "Digite sua resposta (A-D): ";

      if (!(std::cin >> ans)) return -1;

      return ans - 'A';
    }

    signed fim (void)
    {
      /* Show ending interface */

      // TODO: Build the end interface

      return 0;
    }

    void ranking (void)
    {
      /* Show ranking interface */

      // TODO: Show ranking

      return;
    }

  } user_interface;

public:

  Program () {}

  signed run_user_interface (void)
  {
    /* Main interface program */

    // TODO: Run interface

    return 0;
  }
};

signed main (void)
{
  /* Main program function */

  return Program().run_user_interface();
}
