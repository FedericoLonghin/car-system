void obdSetup()
{
  while (true)
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
      break;
    }
  }
  if (smartSearch)
  {
    int s = 0;
    for (int pid = 0; pid < 1000; pid++)
    {
      Serial.print(pid);
      Serial.print(" ; ");
      Serial.print(OBD2.pidName(pid));
      Serial.print(" ; ");
      Serial.print(OBD2.pidReadRaw(pid));
      Serial.print(" ; ");
      Serial.print(OBD2.pidRead(pid));
      if (OBD2.pidSupported(pid))
      {
        // PID supported, continue to next one ...
        s++;
        Serial.print(" ; supported");
      }
      Serial.println("");
    }
    // Serial.print("Alvalieble ");
    // Serial.print(s);
    // Serial.println(" supported pids");

    //todo smart indexing
  }
}

ReturnType getPidsValue(int pid, float &value)
{

  if (!OBD2.pidSupported(pid))
  {
    // PID not supported, continue to next one ...
    return Error;
  }

  // print PID name
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
  if (smartSearch)
  {
  }
  else
  {
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
        dati[pid] = 0;
      }
    }
  }
}
