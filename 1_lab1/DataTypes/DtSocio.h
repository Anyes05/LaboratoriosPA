#ifndef DTSOCIO_H
#define DTSOCIO_H
using namespace std;

class DtSocio
{
    private:
        string CI;
        string nombre;
    public:
        DtSocio(string, string);
        string getCi();
        string getNombre();
        virtual ~DtSocio();        

};

#endif