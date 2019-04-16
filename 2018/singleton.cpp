class Singleton
{
private: 
static mutex m_mtx;
static Singleton *m_pInstance;
Singleton(){}
~Singleton(){}
public:
static Singleton* getInstance()
{
    if(nullptr == m_pInstance)
    {
        m_mtx.lock();
        if (nullptr == m_pInstance)
        {
            m_pInstance = new Singleton;
        }
    }
}
};
mutex Singleton::m_mtx = NULL;
Singleton Singleton::m_pInstance = NULL;
