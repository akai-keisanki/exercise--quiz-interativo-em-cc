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

      while (!perguntas_txt.eof())
      {
        Pergunta p;

        std::getline(perguntas_txt, stmp);
        p.enunciado.assign(stmp);

        for (std::string& s : p.questoes)
        {
          std::getline(perguntas_txt, stmp);
          s.assign(stmp);
        }

        if (!std::getline(perguntas_txt, stmp)) return 1;
        p.resposta = stmp[0];
        
        perguntas.push_back(p);
      }

      perguntas_txt.close();

      // Reading the ranking

      std::ifstream ranking_txt ("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      while (!ranking_txt.eof())
      {
        Jogador j;

        perguntas_txt >> j.nome >> j.pontuacao;

        ranking.push_back(j);
      }
      
      ranking_txt.close();

      return 0;
    }

    signed update_data (void)
    {
      /* Disk data updating */

      // TODO: Make disk data updating
      
      return 0;
    };

  } data;

  class UserInterface
  {
  public:

    signed perguntar (Data::Pergunta p)
    { 
      /* Show question interface */

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
