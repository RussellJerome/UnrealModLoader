#pragma once
#include "UObject/Object.h"

namespace UE4
{
	//Implementing here as it is a useless class
	class UMovieSceneSignedObject : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class MovieScene.MovieSceneSignedObject");
			return ptr;
		}

	};

	//Implementing here as it is a useless class
	class UMovieSceneSequence : public UMovieSceneSignedObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class MovieScene.MovieSceneSequence");
			return ptr;
		}
	};

	class UWidgetAnimation : public UMovieSceneSequence
	{
	public:
		float GetStartTime();
		float GetEndTime();

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.WidgetAnimation");
			return ptr;
		}
	};
};