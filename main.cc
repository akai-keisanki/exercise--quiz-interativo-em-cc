#include <cstddef>

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <array>
#include <vector>

// Program class

class QuizProgram
{
protected:

  class Data
  {
  public:

    /* Disk data initialization process */

    Data ()
    {
      if (load_data())
        std::cerr << "Erro: Arquivo 'perguntas.txt' ou 'ranking.txt' nao encontrado ou invalido para leitura." << std::endl;
    }

    ~ Data ()
    {
      if (update_data())
        std::cerr << "Erro: Arquivo 'ranking.txt' nao encontrado ou invalido para escrita." << std::endl;
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
    std::vector<Jogador> ranking;

    /* Disk data manipulation functions */
    
    signed load_data (void)
    {
      /* Disk data loading */

      // Reading the questions

      std::ifstream perguntas_txt;
      perguntas_txt.open("perguntas.txt");
      if (!perguntas_txt.is_open()) return -1;

      std::string stmp;

      while (!perguntas_txt.eof())
      {
        Pergunta p;

        if (!std::getline(perguntas_txt, p.enunciado)) return 1;

        for (std::string& s : p.questoes)
          if (!std::getline(perguntas_txt, s)) return 1;

        std::getline(perguntas_txt, stmp);
        p.resposta = stmp[0] - 'A';
        
        perguntas.push_back(p);

        if (perguntas_txt.eof()) break;

        std::getline(perguntas_txt, stmp);
      }

      perguntas_txt.close();

      // Reading the ranking

      std::ifstream ranking_txt;
      ranking_txt.open("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      while (!ranking_txt.eof())
      {
        Jogador j;

        ranking_txt >> j.nome >> j.pontuacao;

        if (ranking_txt.bad()) return 1;

        ranking.push_back(j);
      }
      
      ranking_txt.close();

      return 0;
    }

    signed update_data (void)
    {
      /* Disk data updating */

      // Writing the ranking

      std::ofstream ranking_txt;
      ranking_txt.open("ranking.txt");
      if (!ranking_txt.is_open()) return -1;
      
      for (Jogador& j : ranking)
        if (!(ranking_txt << j.nome << ' ' << j.pontuacao << std::endl)) return 1;
      
      ranking_txt.close();

      return 0;
    };

  } data;

  class UserInterface
  {
  public:

    char perguntar (const size_t& i, const Data::Pergunta& p)
    { 
      /* Show question interface for question `i` */

      // Variables
      char ans;

      // Question output

      std::cout << "Pergunta " << i << ':' << std::endl ;

      std::cout << p.enunciado << std::endl << std::endl;

      for (const std::string& s : p.questoes)
        std::cout << s << std::endl;

      // Answer input

      std::cout << std::endl << "Digite sua resposta (A-D): ";

      if (!(std::cin >> ans)) return -1;

      while (true)
      {
        if (ans >= 'A' && ans <= 'D')
        {
          ans -= 'A';
          break;
        }
        if (ans >= 'a' && ans <= 'd')
        {
          ans -= 'a';
          break;
        }

        std::cout << "Opcao invalida. Digite novamente (A-D): ";
        if (!(std::cin >> ans)) return -1;
      }

      // Return of answer
      return ans;
    }

    std::string fim (const size_t& points, const size_t& total)
    {
      /* Show ending interface */

      // Variables
      std::string s;

      // Ending output

      std::cout << "Quiz finalizado!" << std::endl
        << "Voce acertou " << points << " de " << total << " perguntas." << std::endl << std::endl
        << "Digite seu primeiro nome: ";

      // Name input

      std::cin >> s;

      // Return of name
      return s;
    }

    void ranking (std::vector<Data::Jogador> ranking)
    {
      /* Show ranking interface */

      // Ranking title
      std::cout << "--- Ranking ---" << std::endl;

      // Ranking

      for (const Data::Jogador& j : ranking)
        std::cout << j.nome << ' ' << j.pontuacao << std::endl;

      return;
    }

  } user_interface;

public:

  QuizProgram () {}

  signed run_user_interface (void)
  {
    /* Main interface program */

    // Variables
    size_t points = 0;
    char ans;

    // Ask the questions and score

    for (size_t i = 0; i < data.perguntas.size(); i ++)
    {
      ans = user_interface.perguntar(i, data.perguntas[i]);

      if (ans < 0)
      {
        std::cerr << "Erro: Não foi possível obter a resposta.";
        return -1;
      }

      // Pontuação
      
      if (ans == data.perguntas[i].resposta) points ++;
    }

    // End

    Data::Jogador j {user_interface.fim(points, data.perguntas.size()), points};

    // Preparando ranking

    std::vector<Data::Jogador>::iterator it = std::find_if(data.ranking.begin(), data.ranking.end(), [j] (const Data::Jogador& ji) { return ji.nome == j.nome; });

    if (it == data.ranking.end())
    {
      data.ranking.push_back(j);
    }
    else
    {
      it->pontuacao = j.pontuacao;
    }

    std::sort(data.ranking.begin(), data.ranking.end(), [] (const Data::Jogador& j1, const Data::Jogador& j2) { return j1.pontuacao > j2.pontuacao; });

    // Ranking
    user_interface.ranking(data.ranking);

    // Sucessful return
    return 0;
  }
};

// Main function

signed main (void)
{
  /* Main program function */

  return QuizProgram().run_user_interface();
}
