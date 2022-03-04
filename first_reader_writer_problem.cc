
using namespace std;

// starve writer
class RWLock
{
private:
    mutex resource, rmtx;
    int rctr;

public:
    void RLock()
    {
        lock_guard<mutex> lg(this->rmtx);
        rctr++;
        if (rctr == 1)
        {
            resource.lock();
        }
    }

    void RUnlock()
    {
        lock_guard<mutex> lg(this->rmtx);
        rctr--;
        if (rctr == 0)
        {
            resource.Unlock();
        }
    }

    void WLock()
    {
        resource.lock();
    }

    void WUnlock()
    {
        resource.Unlock();
    }
};
