# **Audio-TS-PP**
Audio basic preprocesing stage, windowing/Framing with overlap if required, detect and remove silence frames and apply a Pre-emphasize filter.\
written in cpp with minimal modification required to use the methods in c. 


# **DEPENDENCIES**
NONE.


# **INSTALLATION**
1- clone the repository.\
2- include the header in the project.


# **USAGE**
1- the audio signal is a continous signal, to process it we should perform windowing/framing (some cases require the frames to be overlapped),then it will be quasi-stationary signal, we then process it frame by frame, use the method `PP_GetOverlappedFrames` to perform convert the signal to the (overlapped if required) frames of equal length.\
2- use the different preprocessing method for each frame according the requirements.

