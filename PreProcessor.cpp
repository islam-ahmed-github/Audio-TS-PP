





 /*
 * PreProcessor.c
 *
 *  Created on: Oct 20, 2020
 *      Author: Islam Ahmed
 */



#include "PreProcessor.h"





PreProcessor::PreProcessor()
{
	//ctor
}

PreProcessor::~PreProcessor()
{
	//dtor
}

 


void  PreProcessor::PP_ApplyPreEmphasizeFilter(short *AudioWav, uint32_t Len, double Coeff, uint32_t FilterOrder)
{
	UINT32 i, t;
	short LastInput = 0;
	for (t = 0; t < FilterOrder; t++)
	{
		LastInput = 0;
		for ( i = 0; i < Len; i++)
		{
			AudioWav[i] = (short)(AudioWav[i] - (short)(Coeff * (double)LastInput));
			LastInput = AudioWav[i];
		}
	}

}

 


double GetPowerSum(const double *Frame, UINT32 FrameLen)
{
	double sum = 0.0;
	for (UINT32 i = 0; i < FrameLen; i++) sum += std::abs(Frame[i]);
	return sum;
}// end function 


ULONG GetPowerSum(const short *Frame, UINT32 FrameLen)
{
	ULONG sum = 0;
	for (UINT32 i = 0; i < FrameLen; i++) sum += std::abs(Frame[i]);
	return sum;
}// end function 

 
UINT32 PreProcessor::PP_RemoveSilenceFrames(short * Frames, UINT32 NumOfFrames, UINT32 FrameLenSamples, USHORT SampleThreshold)
{
	ULONG NewNumOfFrames = 0, Psum = 0, index = 0;
	short * SrcFrameOffset = Frames;
	double Threshold = SampleThreshold * FrameLenSamples;
	for (UINT32 FrameIndex = 0; FrameIndex <NumOfFrames; FrameIndex++)
	{
		SrcFrameOffset = (short*)(Frames + (FrameLenSamples*FrameIndex));
		Psum = GetPowerSum(SrcFrameOffset, FrameLenSamples);

		if (Psum > Threshold)
		{
			for (UINT32 SampleIndex = 0; SampleIndex < FrameLenSamples; SampleIndex++)
			{
				Frames[index] = Frames[(FrameIndex*FrameLenSamples) + SampleIndex];
				index++;
			}
			NewNumOfFrames++;
		}
	}
	return NewNumOfFrames;
}


UINT32 PreProcessor::PP_RemoveSilenceFrames(double * Frames, UINT32 NumOfFrames, UINT32 FrameLenSamples, USHORT SampleThreshold)
{
	ULONG NewNumOfFrames = 0, Psum = 0, index = 0;
	double* SrcFrameOffset = Frames;
	double Threshold = SampleThreshold * FrameLenSamples;
	for (UINT32 FrameIndex = 0; FrameIndex <NumOfFrames; FrameIndex++)
	{
		SrcFrameOffset = (double*)(Frames + (FrameLenSamples*FrameIndex));
		Psum = GetPowerSum(SrcFrameOffset, FrameLenSamples);

		if (Psum > Threshold)
		{
			for (UINT32 SampleIndex = 0; SampleIndex < FrameLenSamples; SampleIndex++)
			{
				Frames[index] = Frames[(FrameIndex*FrameLenSamples) + SampleIndex];
				index++;
			}
			NewNumOfFrames++;
		}
	}
	return NewNumOfFrames;
}


 


void PreProcessor::PP_GetOverlappedFrames(short *RawAudioData, UINT32 RawAudioDataLen, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS, short* Output)
{

	UINT32 FrameSamples, ShiftSamples, OverlapSamples, NumOfFrames;

	FrameSamples = (UINT32)(SamplingRateHz*((double)FrameDurationMS / 1000.0));
	OverlapSamples = (UINT32)(SamplingRateHz*((double)OverlapDurationMS / 1000.0));
	ShiftSamples = FrameSamples - OverlapSamples;
	NumOfFrames = ((RawAudioDataLen - OverlapSamples) / (FrameSamples - OverlapSamples));

	for (ULONG FrameIndex = 0; FrameIndex < NumOfFrames; FrameIndex++)
	{
		for (ULONG SampleIndex = 0; SampleIndex < FrameSamples; SampleIndex++)
		{
			Output[MACRO_GetArrayIndex(FrameIndex, SampleIndex, FrameSamples)] = RawAudioData[(FrameIndex*ShiftSamples) + SampleIndex];
		}
	}
}





void PreProcessor::PP_GetOverlappedFrames(short *RawAudioData, UINT32 RawAudioDataLen, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS, double* Output)
{

	ULONG FrameSamples, ShiftSamples, OverlapSamples, NumOfFrames;

	FrameSamples = (UINT32)(SamplingRateHz*((double)FrameDurationMS /  1000.0));
	OverlapSamples = (UINT32)(SamplingRateHz*((double)OverlapDurationMS / 1000.0));
	ShiftSamples = FrameSamples - OverlapSamples;
	NumOfFrames = ((RawAudioDataLen - OverlapSamples) / (FrameSamples - OverlapSamples));

	for (ULONG FrameIndex = 0; FrameIndex < NumOfFrames; FrameIndex++)
	{
		for (ULONG SampleIndex = 0; SampleIndex < FrameSamples; SampleIndex++)
		{
			Output[MACRO_GetArrayIndex(FrameIndex, SampleIndex, FrameSamples)] = RawAudioData[(FrameIndex*ShiftSamples) + SampleIndex];
		}
	}
}







UINT32 PreProcessor::PP_GetNumOfOverlappedFrames(ULONG RawAudioLengthSamples, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS)
{

	ULONG FrameSamples, OverlapSamples, NumOfFrames;

	FrameSamples = (ULONG)(SamplingRateHz * ((double)FrameDurationMS / 1000.0));
	OverlapSamples = (ULONG)(SamplingRateHz * ((double)OverlapDurationMS / 1000.0));
	NumOfFrames = ((RawAudioLengthSamples - OverlapSamples) / (FrameSamples - OverlapSamples));

	return NumOfFrames;
}





ULONG PP_ConvertTimeMsToSamples(double Tms, UINT32 SRhz)
{
	return (ULONG)(SRhz * (Tms / 1000.0));
}


ULONG PP_ConvertSamplesToTimeMs(ULONG Nsamples, UINT32 SRhz)
{
	return (ULONG)(Nsamples/SRhz)*1000.0;
}




