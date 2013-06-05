#ifndef SINGLETON_H
#define SINGLETON_H

template<class SingletonName>
class Singleton{

	public:
		static SingletonName&					getInstance(){
			if( s_inst == NULL )
				s_inst = new SingletonName();
			return (*s_inst);
		}

		static void								destroy(){
			if( s_inst != NULL )
				delete s_inst;
		}

	private:
		// Singleton
		Singleton(){}														// Forbid direct creation
		Singleton(const Singleton& nm);										// Forbid copy
		Singleton&							operator=(const Singleton& n);	// Forbid copy
		virtual ~Singleton(){}												// Forbid direct destruction
		static SingletonName *					s_inst;						// Singleton timekeeper
}

#endif // SINGLETON_H
