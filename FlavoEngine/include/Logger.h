// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//Get custom <LogA> logger
#define VLogA (Internal::VLog::GetInstance().GetCustomLogA())
//Get custom <LogB> logger
#define VLogB (Internal::VLog::GetInstance().GetCustomLogB())
//Get custom <LogC> logger
#define VLogC (Internal::VLog::GetInstance().GetCustomLogC())
//Get custom <LogD> logger
#define VLogD (Internal::VLog::GetInstance().GetCustomLogD())

//Get <Null> logger
#define VLogN (Internal::VLog::GetInstance().GetNullLog())
//Get <Warning> logger
#define VLogW (Internal::VLog::GetInstance().GetWarningLog())
//Get <Error> logger
#define VLogR (Internal::VLog::GetInstance().GetErrorLog())

#define _FILE_ Internal::VLog::GetRelativeFileName(__FILE__)
#define _LINE_ Internal::VLog::GetLine(__LINE__)

namespace Internal
{
	class LoggerInit {
	public:
		fstream LogFile;
		LoggerInit() {
			string prefix = "../../";
			string activeLogFile = "Log.flog";

			string name;
			fstream tmp = fstream(activeLogFile, fstream::in);
			getline(tmp, name);
			if (name != "") {
				string tmpStr = prefix;
				tmpStr.append(name);
				name = tmpStr;
				fstream oldLog = fstream(name, fstream::out);
				while (getline(tmp, tmpStr)) oldLog << tmpStr << '\n';
			}
			tmp.close();
			LogFile = fstream(activeLogFile, fstream::out | fstream::trunc);
			LogFile << time(0) << ".flog\n";
		}
	};

	class Logger {
	private:
		string type;
		LoggerInit* TemporaryLogFile;

		template<class DT, class ...T>
		void LogHelper(DT arg, T... args) {
			TemporaryLogFile->LogFile << arg << " | ";
			LogHelper(args...);
		}

		template<class DT>
		void LogHelper(DT arg) {
			TemporaryLogFile->LogFile << arg;
		}

	public:
		Logger() { }
		Logger(string _type, LoggerInit* TmpLogFile) : type(_type), TemporaryLogFile(TmpLogFile) { }

		template<class ...T>
		void operator() (T... args) {
			TemporaryLogFile->LogFile << type << ' ';
			LogHelper(args...);
			TemporaryLogFile->LogFile << endl;
		}

		template<class T>
		Logger& operator << (T arg) {
			TemporaryLogFile->LogFile << type << arg << endl;
			return *this;
		}
	};

	class VLog
	{
	private:
		VLog() {
			LoggerInit* logFile = new LoggerInit();

			LogA = new Logger("<LogA> ", logFile);
			LogB = new Logger("<LogB> ", logFile);
			LogC = new Logger("<LogC> ", logFile);
			LogD = new Logger("<LogD> ", logFile);

			LogW = new Logger("<Warning> ", logFile);
			LogR = new Logger("<Error> ", logFile);
			LogN = new Logger("<Null> ", logFile);
		}

		Logger* LogA;
		Logger* LogB;
		Logger* LogC;
		Logger* LogD;

		Logger* LogW;
		Logger* LogR;
		Logger* LogN;

	public:
		VLog(VLog const&) = delete;
		void operator=(VLog const&) = delete;

		static VLog& GetInstance() {
			static VLog instance;
			return instance;
		}

		static string GetLine(int LineNr) {
			return ("Line: " + to_string(LineNr));
		}

		static string GetRelativeFileName(string FullPath) {
			size_t lastDelimiterPos = FullPath.find_last_of('\\');
			if (lastDelimiterPos == string::npos) {
				lastDelimiterPos = FullPath.find_last_of('/');
				if (lastDelimiterPos == string::npos)
					return FullPath;
			}

			size_t substringStartPos = FullPath.find_last_of('\\', lastDelimiterPos - 1);
			if (substringStartPos == string::npos) {
				substringStartPos = FullPath.find_last_of('/', lastDelimiterPos - 1);
				if (substringStartPos == string::npos)
					return FullPath;
			}

			return FullPath.substr(substringStartPos + 1, FullPath.length() - substringStartPos - 1);
		}

		Logger& GetCustomLogA() const { return *LogA; }
		Logger& GetCustomLogB() const { return *LogB; }
		Logger& GetCustomLogC() const { return *LogC; }
		Logger& GetCustomLogD() const { return *LogD; }

		Logger& GetWarningLog() const { return *LogW; }
		Logger& GetErrorLog() const { return *LogR; }
		Logger& GetNullLog() const { return *LogN; }
	};
}

