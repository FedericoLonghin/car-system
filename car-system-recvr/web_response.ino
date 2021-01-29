
void handleRoot() {
  fetchData();
  Serial.println(speed);
  Serial.println("Request from client on /");
  String response = "{";
  response += "'driver':{";
  response += " 'id':4,";
  response += " 'name':'Samuele',";
  response += " 'img_url':'https://scontent-mxp1-1.cdninstagram.com/v/t51.2885-19/s320x320/64701390_344591192884614_2195287428573429760_n.jpg?_nc_ht=scontent-mxp1-1.cdninstagram.com&_nc_ohc=Xn33Cn5QZn0AX_cu6cT&tp=1&oh=182791d27f500894398cf5f9cff0dc4d&oe=600C5751'";
  response += " },";
  response += "  'speed':"+speed+",";
  response += " 'rpm':"+rpm+",";
  response += "  'max_speed':55,";
//  response += " 'errors':[";
//  response += "  {";
//  response += " 'id':'Door_FR',";
//  response += " 'text':'Portiera del passeggero aperta',";
//  response += "  'valueS':'https://cdn1.iconfinder.com/data/icons/car-engine-dashboard-lights-solid-style-set-2/91/Car_Engine_-_Dashboard_Lights_69-512.png'";
//  response += "}";
//  response += "   ]";
  response += "}";
  server.send(200, "text/html", response);
}
