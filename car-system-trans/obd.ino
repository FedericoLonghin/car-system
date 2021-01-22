typedef enum valueType {
  Raw = 1,
  Clear = 2,
  Error = 0,
} returnType;

returnType processPid(int pid, float &value);

void obdSetup() {
  while (true) {
    Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));

    if (!OBD2.begin()) {
      Serial.println(F("failed!"));

      delay(1000);
    } else {
      Serial.println(F("success"));
      break;
    }
  }
}

returnType processPid(int pid, float &value) {
  if (!OBD2.pidSupported(pid)) {
    // PID not supported, continue to next one ...
    return Error;
  }

  // print PID name
  Serial.print(OBD2.pidName(pid));
  Serial.print(F(" = "));

  if (OBD2.pidValueRaw(pid)) {
    // read the raw PID value
    unsigned long pidRawValue = OBD2.pidReadRaw(pid);

    Serial.print(F("0x"));
    Serial.print(pidRawValue, HEX);
    value = pidRawValue;
    return Raw;
  } else {
    // read the PID value
    float pidValue = OBD2.pidRead(pid);

    if (isnan(pidValue)) {
      Serial.print("error");
    } else {
      // print value with units

      Serial.print(pidValue);
      Serial.print(F(" "));
      Serial.print(OBD2.pidUnits(pid));
      value = pidValue;
    }
  }

  Serial.println();
  return Clear;
}
