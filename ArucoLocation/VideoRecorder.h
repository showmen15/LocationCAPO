#ifndef VIDEORECORDER_H_
#define VIDEORECORDER_H_

#include <iostream>


class VideoRecorder
{
public:
	VideoRecorder(void);
	~VideoRecorder(void);

	StartRecord(string sFileName);
};

#endif /* VIDEORECORDER_H_ */