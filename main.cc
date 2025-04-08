#include <cstddef>

#include <string>
#include <iostream>
#include <fstream>

#include <array>
#include <vector>

class Program
{
protected:

  class Data
  {
  public:

    struct Pergunta
    {
      std::string enunciado;
      std::array<std::string, 4> questoes;
      char resposta;
    };

    std::vector<Pergunta> perguntas;
    
    signed load_data (void)
    {
      std::ifstream perguntas_txt ("perguntas.txt");
      if (!perguntas_txt.is_open()) return -1;

      std::ifstream ranking_txt ("ranking.txt");
      if (!ranking_txt.is_open()) return -1;

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

      // TODO: Read ranking

      perguntas_txt.close();
      ranking_txt.close();

      return 0;
    }

  } data;

  class UserInterface
  {
  public:

    signed perguntar (Data::Pergunta p)
    {
      // TODO: Build question interface

      return -1;
    }

    signed fim (void)
    {
      return 0;
    }

    void ranking (void)
    {
      // TODO: Show ranking

      return;
    }

  } user_interface;

public:

  void main (void)
  {
    // TODO: Run interface

    return;
  }
};

signed main (void)
{
  Program program;
  program.main();
  return 0;
}
