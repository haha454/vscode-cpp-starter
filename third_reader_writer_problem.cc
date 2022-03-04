using namespace std;

// starve reader
class RWLock
{
private:
    mutex rmtx;
    binary_semaphore resource;
    FairBinarySemaphore fbs;
    int rctr;

public:
    void RLock()
    {
        lock_guard<mutex> lg(this->rmtx);
        fs.acquire();
        rctr++;
        if (rctr == 1)
        {
            resource.lock();
        }
        fs.release();
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
        fs.acquire();
        resource.acquire();
        fs.release();
    }

    void WUnlock()
    {
        resource.release();
    }
};
