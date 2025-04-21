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
        std::cerr << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido." << std::endl;
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
        p.resposta = stmp[0];
        
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
        perguntas_txt << p.enunciado << std::endl;

        for (const std::string& s : p.questoes)
          perguntas_txt << s << std::endl;

        perguntas_txt << p.resposta << std::endl << std::endl;
      }

      perguntas_txt.close();
      
      // Reading the ranking

      std::ofstream ranking_txt ("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      for (Jogador& j : ranking)
      {
        perguntas_txt << j.nome << j.pontuacao;
      }
      
      ranking_txt.close();

      return 0;
    };

  } data;

  class UserInterface
  {
  public:

    signed perguntar (const size_t& i)
    { 
      /* Show question interface for question `i` */

      // TODO: Build question interface

      return -1;
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
