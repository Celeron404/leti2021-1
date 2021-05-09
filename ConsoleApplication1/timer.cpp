#include <chrono>
using namespace std::chrono;

float stopSecondsTimer(time_point<steady_clock> startTimer) {
	using fseconds = duration<float>; // ����������� ���������� ��������� ������� ��� ����������� ������� ������ � �������.
	time_point<steady_clock> endTimer = steady_clock::now(); // ��������� �������
	fseconds sortingTime = duration_cast<fseconds>(endTimer - startTimer); // ���������� ������� ����� ��������� � ��������� ��������
	return sortingTime.count();
}

long long stopNanoSecondsTimer(time_point<steady_clock> startTimer) {
	time_point<steady_clock> endTimer = steady_clock::now();
	nanoseconds sortingTime = duration_cast<nanoseconds>(endTimer - startTimer);
	return sortingTime.count();
}