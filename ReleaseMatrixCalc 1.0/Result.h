#pragma once
class Oper {
public:
	virtual void getres() = 0;
};
class Res {
public:
	void getres(Oper* oper) {
		oper->getres();
	}
};