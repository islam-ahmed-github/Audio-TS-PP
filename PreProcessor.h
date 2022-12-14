


 /*
 * PreProcessor.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Islam Ahmed
 */








#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H


#include<stdint.h>
#include<cmath>
#include<limits.h>
#include<float.h>


#define PI (3.14159265358979323846)

#define MACRO_GetArrayIndex(RowIndex,ColIndex,RowLength)  (((RowIndex)*RowLength)+(ColIndex))



class PreProcessor
{
public:
	PreProcessor();
	virtual ~PreProcessor();
	void   PP_ApplyPreEmphasizeFilter(short *AudioWav, uint32_t Len, double Coeff, uint32_t FilterOrder);
	UINT32 PP_RemoveSilenceFrames(short * Frames, UINT32 NumOfFrames, UINT32 FrameLenSamples, USHORT SampleThreshold);
	UINT32 PP_RemoveSilenceFrames(double * Frames, UINT32 NumOfFrames, UINT32 FrameLenSamples, USHORT SampleThreshold);
	void   PP_GetOverlappedFrames(short *RawAudioData, UINT32 RawAudioDataLen, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS, short* Output);
	void   PP_GetOverlappedFrames(short *RawAudioData, UINT32 RawAudioDataLen, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS, double* Output);
	UINT32 PP_GetNumOfOverlappedFrames(ULONG RawAudioLengthSamples, UINT32 SamplingRateHz, UINT32 FrameDurationMS, UINT32 OverlapDurationMS);

	 

protected:

private:


};

#endif // PREPROCESSOR_H
