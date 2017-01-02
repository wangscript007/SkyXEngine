
#ifndef s4g_compiler_h
#define s4g_compiler_h

struct s4g_command
{
	s4g_command(){ command = mc_halt; arg = 0; lexid = -1; }
	~s4g_command(){}
	s4g_command(s4g_vm_command comm, s4g_value* val, long _lexid){ command = comm; arg = val; lexid = _lexid; }
	s4g_vm_command command;
	s4g_value* arg;
	long lexid;
};

class s4g_compiler
{
public:
	s4g_compiler(){ gc = 0; comms = 0; oldop = (s4g_type_op)0; }
	~s4g_compiler(){}
	inline void gen(s4g_vm_command comm,s4g_value* val,long _lexid = -1);
	int compile(s4g_node* node, s4g_stack<s4g_command> * commands);
	int compile2(s4g_node* node);
//protected:
	s4g_type_op oldop;
	s4g_stack<s4g_command,16>* comms;
	s4g_gc* gc;
	struct _cyctl
	{
		int addr;
		enum
		{
			BREAK,
			CONTINUE
		}
		type;
	};
	s4g_stack<Array<_cyctl>> cyctls_bak;
	Array<_cyctl> cyctls;
};

#endif 