void obdSetup()
{
  for (int t = 0; t < 2; t++)
  {
    Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));
    if (!OBD2.begin())
    {
      Serial.println(F("failed!"));
      delay(1000);
    }
    else
    {
      Serial.println(F("success"));
      obdStatus = 1;
      break;
    }
  }
  dati = new float[maxPidsCount];
}

ReturnType getPidsValue(int pid, float &value)
{

  if ( !obdStatus || !OBD2.pidSupported(pid) )
  {
    // PID not supported, continue to next one ...
    Serial.print(OBD2.pidName(pid));
    Serial.println(" Not supported");
    return Error;
  }

  Serial.print(OBD2.pidName(pid));
  Serial.print(F(" = "));

  if (OBD2.pidValueRaw(pid))
  {
    // read the raw PID value
    unsigned long pidRawValue = OBD2.pidReadRaw(pid);

    Serial.print(F("0x"));
    Serial.print(pidRawValue, HEX);
    value = pidRawValue;
    return Raw;
  }
  else
  {
    // read the PID value
    float pidValue = OBD2.pidRead(pid);

    if (isnan(pidValue))
    {
      Serial.print("error");
    }
    else
    {
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

void fetchData()
{
  if (!obdStatus)return;
  for (int pid = 0; pid < maxPidsCount; pid++)
  {
    float result;
    ReturnType returnType = getPidsValue(pid, result);
    if (returnType != Error)
    {
      dati[pid] = result;
    }
    else
    {
      dati[pid] = NULL;
    }
  }
}
