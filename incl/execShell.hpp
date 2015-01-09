/*
Вспомогательный класс для выполнения комманд
Предоставляет возможность выполнять комманды с
заданным Тайм-аутом 
*/
#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using namespace std;

class ExecShell
{
	public:
		static string exec(string cmd, unsigned int time_out);		//Выполнить комманду с заданным тайм-аутом
		static string getNameOfUtility(string str);			//Извлечь имя утилиты из строки запуска утилит
	private:
		static void executionThread(string *cmdRes, bool *canceled);	//Поток выполнения комманды
};
