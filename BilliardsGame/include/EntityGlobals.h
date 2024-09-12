#pragma once

enum BallId
{
	BallId_cueBall,		//	0
	BallId_one,			//	1
	BallId_two,			//	2
	BallId_three,		//	3
	BallId_four,		//	4
	BallId_five,		//	5
	BallId_six,			//	6
	BallId_seven,		//	7
	BallId_eight,		//	8
	BallId_nine,		//	9
	BallId_ten,			//	10
	BallId_eleven,		//	11
	BallId_twelve,		//	12
	BallId_thirteen,	//	13
	BallId_fourteen,	//	14
	BallId_fifteen,		//	15
	BallId_MAX_BALL_ID	//	16
};

namespace PoolBall
{
	extern int radius;
	extern float tagScale;
}

namespace PoolTable
{
	extern int height;
	extern int width;
}