#ifndef TINYGS_IMPROV_H
#include <Arduino.h>
#include <improv.h>

typedef std::function<void ()> onConnected_t;
// Improv
void handleImprovPacket ();
void initImprovVersionInfo (uint32_t version);
void improvOnConnected (onConnected_t callback);

#endif // TINYGS_IMPROV_H