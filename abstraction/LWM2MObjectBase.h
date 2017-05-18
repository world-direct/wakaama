#ifndef LWM2MOBJECTBASE_H
#define LWM2MOBJECTBASE_H

extern "C"{
    #include "liblwm2m.h"
}

class LWM2MObjectBase{

    public:
		LWM2MObjectBase(uint16_t objID);
        lwm2m_object_t * GetLWM2MObject(void);

    protected:
        virtual uint8_t Read(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP) = 0;
        virtual uint8_t Write(uint16_t instanceId, int numData, lwm2m_data_t * dataArrayP) = 0;
        virtual uint8_t Execute(uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length) = 0;
        virtual uint8_t Discover(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP) = 0;
        virtual uint8_t Create(uint16_t instanceId, int numData, lwm2m_data_t * dataArray) = 0;
        virtual uint8_t Delete(uint16_t instanceId) = 0;

    private:
                
        lwm2m_object_t _lwm2mObject;

        static uint8_t LWM2M_Read(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP);
        static uint8_t LWM2M_Write(uint16_t instanceId, int numData, lwm2m_data_t * dataArrayP, lwm2m_object_t * objectP);
        static uint8_t LWM2M_Execute(uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length, lwm2m_object_t * objectP);
        static uint8_t LWM2M_Discover(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP);
        static uint8_t LWM2M_Create(uint16_t instanceId, int numData, lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
        static uint8_t LWM2M_Delete(uint16_t instanceId, lwm2m_object_t * objectP);

};

#endif
