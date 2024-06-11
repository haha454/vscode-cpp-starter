using namespace std;

// starve reader
class RWLock
{
private:
    mutex rmtx, wmtx;
    binary_semaphore resource, tryread;
    int rctr, wctr;

public:
    void RLock()
    {
        tryread.acquire();
        lock_guard<mutex> lg(this->rmtx);
        rctr++;
        if (rctr == 1)
        {
            resource.acquire();
        }
        tryread.release();
    }

    void RUnlock()
    {
        lock_guard<mutex> lg(this->rmtx);
        rctr--;
        if (rctr == 0)
        {
            resource.release();
        }
    }

    void WLock()
    {
        lock_guard<mutex> lg(this->wmtx);
        wctr++;
        if (wctr == 1) {
            tryread.acquire();
        }
        resource.acquire();
    }

    void WUnlock()
    {
        lock_guard<mutex> lg(this->wmtx);
        wctr--;
        if (wctr == 0) {
            tryread.release();
        }
        resource.release();
    }
};
