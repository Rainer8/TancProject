#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Tanc {
private:
	string denumire;
	int nrEchipaj;
	string* NumeEchipaj;
	float calibru;
public:
	Tanc() {
		this->denumire = "Nu are";
		this->nrEchipaj = 0;
		this->NumeEchipaj = NULL;
		this->calibru = 0.0;
	}

	Tanc(string den, float cal, int nr, string* nm) {
		this->denumire = den;
		this->calibru = cal;
		this->nrEchipaj = nr;
		this->NumeEchipaj = new string[this->nrEchipaj];
		for (int i = 0; i < this->nrEchipaj; i++)
			this->NumeEchipaj[i] = nm[i];
	}

	Tanc(const Tanc & a) {
		this->denumire = a.denumire;
		this->calibru = a.calibru;
		this->nrEchipaj = a.nrEchipaj;
		this->NumeEchipaj = new string[this->nrEchipaj];
		for (int i = 0; i < this->nrEchipaj; i++)
			this->NumeEchipaj[i] = a.NumeEchipaj[i];
	}

	Tanc & operator=(Tanc &a) {
		this->denumire = a.denumire;
		this->calibru = a.calibru;
		this->nrEchipaj = a.nrEchipaj;
		this->NumeEchipaj = new string[this->nrEchipaj];
		for (int i = 0; i < this->nrEchipaj; i++)
			this->NumeEchipaj[i] = a.NumeEchipaj[i];
		return *this;
	}

	void setDenumire(string den) {
		this->denumire = den;
	}

	string getDenumire() {
		return this->denumire;
	}

	void setCalibru(float cal) {
		if (cal < 1.0)
			throw new exception("ErrCal");
		else
		this->calibru = cal;
	}

	float getCalibru() {
		return this->calibru;
	}

	~Tanc() {
		if (this->NumeEchipaj != NULL)
			delete[]this->NumeEchipaj;
	}

	float getPutereImpact() {
		float p = this->calibru*this->nrEchipaj;
		return p;
	}

	Tanc & operator--(int) {
		this->calibru -= 10.0;
		return *this;
	}

	Tanc & operator+(float x) {
		this->calibru += x;
		return *this;
	}

	string operator[](int i) {
		return this->NumeEchipaj[i];
	}

	friend ostream & operator<<(ostream& out, Tanc & a) {
		out << "\nDenumire: " << a.getDenumire();
		out << "\nCalibru: " << a.getCalibru();
		out << "\n Echipaj: ";
		for (int i = 0; i < a.nrEchipaj; i++)
			out << " | " << a.NumeEchipaj[i];
		return out;
	}

	friend ifstream & operator>>(ifstream& in, Tanc & a) {
		//cout << "\nDenumire: ";
		in>> a.denumire;
		//cout << "\nCalibru: ";
		in>> a.calibru;
		//cout << "\n Nr Echipaj: ";
		in >> a.nrEchipaj;
		if (a.NumeEchipaj != NULL)
			delete[]a.NumeEchipaj;
		a.NumeEchipaj = new string[a.nrEchipaj];
		for (int i = 0; i < a.nrEchipaj; i++)
			in>> a.NumeEchipaj[i];
		return in;
	}
};

class Armata {
private:
	Tanc tanc;
	int nrTancuri;
public:
	Armata() {
		Tanc tx;
		this->tanc =tx;
		this->nrTancuri = 0;
	}

	Armata(Tanc a, int nr) {
		this->tanc = a;
		this->nrTancuri = nr;
	}

	Armata(Armata &a) {
		this->nrTancuri = a.nrTancuri;
		this->tanc = a.tanc;
	}

	Armata & operator=(Armata &a) {
		this->nrTancuri = a.nrTancuri;
		this->tanc = a.tanc;
		return *this;
	}

	friend ostream & operator<<(ostream & out, Armata &a) {
		out << endl << a.tanc;
		out <<endl<< "Nr Tancuri: " << a.nrTancuri;
		return out;
	}

};

class TancMod :public Tanc {
private:
	string denumireModificare;
	float calibruModificare;
public:
	TancMod() {
		this->denumireModificare = "Nu are";
		this->calibruModificare = 0.0;
	}

	TancMod(string den, float cal, int nr, string* nm, string denm, float calm) :Tanc(den, cal, nr, nm) {
		this->denumireModificare = denm;
		this->calibruModificare = calm;
	}

	friend ostream & operator<<(ostream& out, TancMod & a) {
		out << endl<<(Tanc&)a;
		out <<endl<< a.denumireModificare;
		out <<endl<< a.calibruModificare;
		return out;
	}
};

int main() {
	Tanc t1;
	string a[3] = { "Ion","Stefan","Andrei" };
	Tanc t2("T-55", 55.7, 3, a);
	Tanc t3 = t2;
	t1 = t2;
	cout <<t2.getCalibru() << endl;
	cout <<t2.getDenumire()<<endl ;
	t2.setCalibru(87.3);
	t2.setDenumire("IS-7");
	cout << t2.getCalibru() << endl;
	cout << t2.getDenumire() << endl;

	cout << t2.getPutereImpact();

	cout << t2;

	cout << t2.getCalibru() << endl;
	t2--;
	cout << t2.getCalibru() << endl;
	t2 + 5;
	cout << t2.getCalibru() << endl;

	ifstream f("date.txt", ios::in);
	Tanc tk[3];
	for (int i = 0; i < 3; i++)
	{
		f >> tk[i];
		cout << tk[i];
	}

	try
	{
		t2.setCalibru(0.0);
	}
	catch (const exception* e)
	{
		cout <<endl<< e->what()<<endl;
		t2.setCalibru(4.5);
	}

	cout << t2.getCalibru() << endl;

	Armata a1(t2, 15);
	cout << a1;

	TancMod tm1("IS-7",33.5,3,a,"Turela Secundara", 13.2);
	cout <<endl<< tm1;
	cout <<endl<< tm1[1];
	return 0;
}