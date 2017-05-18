#ifndef _PointATC3DG_
#define _PointATC3DG_

// Device USB Vendor ID (idVendor)
enum BirdVendor {
    ASCENSION = 0x21e2
};

// Device USB Product ID (idProduct)
enum BirdProduct {
    MEDSAFE = 0x1003,
    TRAKSTAR = 0x1005,
    DRIVEBAY2 = 0x1008,
};

const int BIRD_EP_OUT = 0x02;
const int BIRD_EP_IN = 0x86;

// forward declarations
struct usb_device;
struct usb_dev_handle;

class PointATC3DG {
public:
    PointATC3DG(unsigned int productId, unsigned int vendorId = ASCENSION);
    ~PointATC3DG();

    // evaluate whether initialized properly
    bool operator!() const;
    bool ok() const;

    int setSuddenOutputChangeLock( int iSensorId );

    int setSensorRotMat( int iSensorId );
    int setSensorTopHemisphere( int iSensorId );
    int setSensorHemisphere( int iSensorId, char cSphereId );
    int setMeasurementRate( double dRate );

    int getNumberOfSensors( void );
    int getCoordinatesAngles( int iSensorId,
        double& dX, double& dY, double& dZ,
        double& dAzimuth, double& dElevation, double& dRoll );
    int getCoordinatesMatrix( int iSensorId,
        double& dX, double& dY, double& dZ,
        double* pMat );

    bool transmitterAttached();
    bool sensorAttached(const int& iSensorId);

protected:
    struct usb_device* find_device( int iVendorId, int iProductId );

    int check_bird_errors( void );
    void error( int val, const char* msg, ... );

protected:
    struct usb_device *dev;
    struct usb_dev_handle *handle;
    
    unsigned int vendorId;
    unsigned int productId;

    char dataout[16];
    char datain[32];

    bool isOk;
    double posk;
};

#endif // _PointATC3DG_

