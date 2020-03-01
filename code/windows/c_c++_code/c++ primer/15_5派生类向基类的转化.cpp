class Base {
public:
	void pub_mem(); // public member
protected:
	int prot_mem; // protected member
private:
	char priv_mem; // private member
};

struct Pub_Derv : public Base {
	// legal
	void memfcn(Base &b) { b = *this; }
};

struct Priv_Derv : private Base {
	// legal
	void memfcn(Base &b) { b = *this; }
};

struct Prot_Derv : protected Base {
	// legal
	void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Public : public Pub_Derv {
	// legal
	void memfcn(Base &b) { b = *this; }
};

/*
struct Derived_from_Private : public Priv_Derv {
	// illegal,because Base对于Derived_fromPrivate来说已经完全不可见了,所以其无法转换为Base
	void memfcn(Base &b) { b = *this; }
};
*/

struct Derived_from_Protected : public Prot_Derv {
	// legal
	void memfcn(Base &b) { b = *this; }
};

int main15_5() {
	return 0;
}