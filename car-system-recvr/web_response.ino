
void handleRoot() {
  fetchData();
  Serial.println("Request from client on /");
  String response = "{"
                    "'driver':{"
                    " 'id':4,"
                    " 'name':'Samuele',"
                    " 'img_url':'https://scontent-mxp1-1.cdninstagram.com/v/t51.2885-19/s320x320/64701390_344591192884614_2195287428573429760_n.jpg?_nc_ht=scontent-mxp1-1.cdninstagram.com&_nc_ohc=Xn33Cn5QZn0AX_cu6cT&tp=1&oh=182791d27f500894398cf5f9cff0dc4d&oe=600C5751'"
                    " },"
                    "  'speed':52,"
                    " 'rpm':5.3,"
                    "  'max_speed':55,"
                    " 'errors':["
                    "  {"
                    " 'id':'Door_FR',"
                    " 'text':'Portiera del passeggero aperta',"
                    "  'valueS':'https://cdn1.iconfinder.com/data/icons/car-engine-dashboard-lights-solid-style-set-2/91/Car_Engine_-_Dashboard_Lights_69-512.png'"
                    "}"
                    "   ]"
                    "}";
  server.send(200, "text/html", response);

}
