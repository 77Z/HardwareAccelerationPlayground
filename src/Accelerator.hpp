#pragma once

class Accelerator {
public:
	Accelerator();
	~Accelerator();

	void onUpdate();

private:

	bool isCudaAvailable();
	bool isOpenCLAvailable();

};