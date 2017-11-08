// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logger.h"

using namespace std;

namespace Internal
{
	// Used to determine macro to use, up to 8 arguments
#define GET_CHECK_MACRO_8(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

	// Wrapper for GET_CHECK_MACRO you need to use in VS
#define EXPAND(x) x

	/*-----------------------------------------------------------------------------------------------------------------------------------*/
	template <class T>
	void _Check(string file, string lineNum, T arg, string name) {
		if (arg == nullptr) {
			VLogN(file, lineNum, name);
		}
	}

	template <class T, class ...Types>
	void _Check(string file, string lineNum, T arg, string name, Types &&...args) {
		if (arg == nullptr) {
			VLogN(file, lineNum, name);
		}
		_Check(file, lineNum, args...);
	}

	// Check macro specializations
#define Check1(a) _Check( _FILE_, _LINE_, a, #a )
#define Check2(a, b) _Check( _FILE_, _LINE_, a, #a, b, #b )
#define Check3(a, b, c) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c )
#define Check4(a, b, c, d) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d )
#define Check5(a, b, c, d, e) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e )
#define Check6(a, b, c, d, e, f) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f )
#define Check7(a, b, c, d, e, f, g) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f, g, #g )
#define Check8(a, b, c, d, e, f, g, h) _Check( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f, g, #g, h, #h )
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
	template <class T>
	bool _BCheck(string file, string lineNum, T arg, string name) {
		if (arg == nullptr) {
			VLogN(file, lineNum, name);
			return false;
		}

		return true;
	}

	template <class T, class ...Types>
	bool _BCheck(string file, string lineNum, T arg, string name, Types &&...args) {
		if (arg == nullptr) {
			VLogN(file, lineNum, name);
			return false;
		}

		return _BCheck(file, lineNum, args...);
	}

	//BCheck macro specializations
#define BCheck1(a) _BCheck( _FILE_, _LINE_, a, #a )
#define BCheck2(a, b) _BCheck( _FILE_, _LINE_, a, #a, b, #b )
#define BCheck3(a, b, c) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c )
#define BCheck4(a, b, c, d) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d )
#define BCheck5(a, b, c, d, e) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e )
#define BCheck6(a, b, c, d, e, f) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f )
#define BCheck7(a, b, c, d, e, f, g) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f, g, #g )
#define BCheck8(a, b, c, d, e, f, g, h) _BCheck( _FILE_, _LINE_, a, #a, b, #b, c, #c, d, #d, e, #e, f, #f, g, #g, h, #h )
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogA1(a) VLogA(_FILE_, _LINE_, a)
#define LogA2(a, b) VLogA(_FILE_, _LINE_, a, b)
#define LogA3(a, b, c) VLogA(_FILE_, _LINE_, a, b, c)
#define LogA4(a, b, c, d) VLogA(_FILE_, _LINE_, a, b, c, d)
#define LogA5(a, b, c, d, e) VLogA(_FILE_, _LINE_, a, b, c, d, e)
#define LogA6(a, b, c, d, e, f) VLogA(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogA7(a, b, c, d, e, f, g) VLogA(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogA8(a, b, c, d, e, f, g, h) VLogA(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogB1(a) VLogB(_FILE_, _LINE_, a)
#define LogB2(a, b) VLogB(_FILE_, _LINE_, a, b)
#define LogB3(a, b, c) VLogB(_FILE_, _LINE_, a, b, c)
#define LogB4(a, b, c, d) VLogB(_FILE_, _LINE_, a, b, c, d)
#define LogB5(a, b, c, d, e) VLogB(_FILE_, _LINE_, a, b, c, d, e)
#define LogB6(a, b, c, d, e, f) VLogB(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogB7(a, b, c, d, e, f, g) VLogB(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogB8(a, b, c, d, e, f, g, h) VLogB(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogC1(a) VLogC(_FILE_, _LINE_, a)
#define LogC2(a, b) VLogC(_FILE_, _LINE_, a, b)
#define LogC3(a, b, c) VLogC(_FILE_, _LINE_, a, b, c)
#define LogC4(a, b, c, d) VLogC(_FILE_, _LINE_, a, b, c, d)
#define LogC5(a, b, c, d, e) VLogC(_FILE_, _LINE_, a, b, c, d, e)
#define LogC6(a, b, c, d, e, f) VLogC(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogC7(a, b, c, d, e, f, g) VLogC(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogC8(a, b, c, d, e, f, g, h) VLogC(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogD1(a) VLogD(_FILE_, _LINE_, a)
#define LogD2(a, b) VLogD(_FILE_, _LINE_, a, b)
#define LogD3(a, b, c) VLogD(_FILE_, _LINE_, a, b, c)
#define LogD4(a, b, c, d) VLogD(_FILE_, _LINE_, a, b, c, d)
#define LogD5(a, b, c, d, e) VLogD(_FILE_, _LINE_, a, b, c, d, e)
#define LogD6(a, b, c, d, e, f) VLogD(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogD7(a, b, c, d, e, f, g) VLogD(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogD8(a, b, c, d, e, f, g, h) VLogD(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogW1(a) VLogW(_FILE_, _LINE_, a)
#define LogW2(a, b) VLogW(_FILE_, _LINE_, a, b)
#define LogW3(a, b, c) VLogW(_FILE_, _LINE_, a, b, c)
#define LogW4(a, b, c, d) VLogW(_FILE_, _LINE_, a, b, c, d)
#define LogW5(a, b, c, d, e) VLogW(_FILE_, _LINE_, a, b, c, d, e)
#define LogW6(a, b, c, d, e, f) VLogW(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogW7(a, b, c, d, e, f, g) VLogW(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogW8(a, b, c, d, e, f, g, h) VLogW(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LogR1(a) VLogR(_FILE_, _LINE_, a)
#define LogR2(a, b) VLogR(_FILE_, _LINE_, a, b)
#define LogR3(a, b, c) VLogR(_FILE_, _LINE_, a, b, c)
#define LogR4(a, b, c, d) VLogR(_FILE_, _LINE_, a, b, c, d)
#define LogR5(a, b, c, d, e) VLogR(_FILE_, _LINE_, a, b, c, d, e)
#define LogR6(a, b, c, d, e, f) VLogR(_FILE_, _LINE_, a, b, c, d, e, f)
#define LogR7(a, b, c, d, e, f, g) VLogR(_FILE_, _LINE_, a, b, c, d, e, f, g)
#define LogR8(a, b, c, d, e, f, g, h) VLogR(_FILE_, _LINE_, a, b, c, d, e, f, g, h)
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
}

namespace Engine
{
	using namespace Internal;

	// Macro used to check nullptrs and log any such occurance
#define Check(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, Check8, Check7, Check6, Check5, Check4, Check3, Check2, Check1) ( __VA_ARGS__ ))
	/**
	* Macro used to check nullptrs, log any such occurance
	* @return True if there are no nullptrs among arguments
	*/
#define BCheck(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, BCheck8, BCheck7, BCheck6, BCheck5, BCheck4, BCheck3, BCheck2, BCheck1) ( __VA_ARGS__ ))

	//Get well-formatting first custom logger
#define LogA(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogA8, LogA7, LogA6, LogA5, LogA4, LogA3, LogA2, LogA1)(__VA_ARGS__))

	//Get well-formatting second custom logger
#define LogB(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogB8, LogB7, LogB6, LogB5, LogB4, LogB3, LogB2, LogB1)(__VA_ARGS__))

	//Get well-formatting third custom logger
#define LogC(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogC8, LogC7, LogC6, LogC5, LogC4, LogC3, LogC2, LogC1)(__VA_ARGS__))

	//Get well-formatting fourth custom logger
#define LogD(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogD8, LogD7, LogD6, LogD5, LogD4, LogD3, LogD2, LogD1)(__VA_ARGS__))

	//Get well-formatting warning logger
#define LogW(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogW8, LogW7, LogW6, LogW5, LogW4, LogW3, LogW2, LogW1)(__VA_ARGS__))

	//Get well-formatting error logger
#define LogR(...) EXPAND(GET_CHECK_MACRO_8(__VA_ARGS__, LogR8, LogR7, LogR6, LogR5, LogR4, LogR3, LogR2, LogR1)(__VA_ARGS__))
}
