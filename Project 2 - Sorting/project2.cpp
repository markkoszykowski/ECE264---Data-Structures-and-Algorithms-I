// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " "
           << pData->firstName << " "
           << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// Mark Koszykowski DSA I Project 2

#include<unordered_map>

// Unordered map that stores unique hash value for each last name
unordered_map<string, long long> LastMap = {
        {"ACOSTA", 1},
        {"ADAMS", 2},
        {"ADKINS", 3},
        {"AGUILAR", 4},
        {"AGUIRRE", 5},
        {"ALEXANDER", 6},
        {"ALLEN", 7},
        {"ALVARADO", 8},
        {"ALVAREZ", 9},
        {"ANDERSON", 10},
        {"ANDREWS", 11},
        {"ARMSTRONG", 12},
        {"ARNOLD", 13},
        {"AUSTIN", 14},
        {"AVILA", 15},
        {"AYALA", 16},
        {"BAILEY", 17},
        {"BAKER", 18},
        {"BALDWIN", 19},
        {"BANKS", 20},
        {"BARBER", 21},
        {"BARKER", 22},
        {"BARNES", 23},
        {"BARNETT", 24},
        {"BARRETT", 25},
        {"BARTON", 26},
        {"BATES", 27},
        {"BECK", 28},
        {"BECKER", 29},
        {"BELL", 30},
        {"BENNETT", 31},
        {"BENSON", 32},
        {"BERRY", 33},
        {"BISHOP", 34},
        {"BLACK", 35},
        {"BLAIR", 36},
        {"BLAKE", 37},
        {"BOWEN", 38},
        {"BOWMAN", 39},
        {"BOYD", 40},
        {"BRADLEY", 41},
        {"BRADY", 42},
        {"BREWER", 43},
        {"BROOKS", 44},
        {"BROWN", 45},
        {"BRYANT", 46},
        {"BURGESS", 47},
        {"BURKE", 48},
        {"BURNS", 49},
        {"BURTON", 50},
        {"BUSH", 51},
        {"BUTLER", 52},
        {"BYRD", 53},
        {"CABRERA", 54},
        {"CALDERON", 55},
        {"CALDWELL", 56},
        {"CAMACHO", 57},
        {"CAMPBELL", 58},
        {"CAMPOS", 59},
        {"CANNON", 60},
        {"CARDENAS", 61},
        {"CARLSON", 62},
        {"CARPENTER", 63},
        {"CARR", 64},
        {"CARRILLO", 65},
        {"CARROLL", 66},
        {"CARTER", 67},
        {"CASTANEDA", 68},
        {"CASTILLO", 69},
        {"CASTRO", 70},
        {"CERVANTES", 71},
        {"CHAMBERS", 72},
        {"CHAN", 73},
        {"CHANDLER", 74},
        {"CHANG", 75},
        {"CHAPMAN", 76},
        {"CHAVEZ", 77},
        {"CHEN", 78},
        {"CHRISTENSEN", 79},
        {"CLARK", 80},
        {"CLARKE", 81},
        {"COHEN", 82},
        {"COLE", 83},
        {"COLEMAN", 84},
        {"COLLINS", 85},
        {"COLON", 86},
        {"CONTRERAS", 87},
        {"COOK", 88},
        {"COOPER", 89},
        {"CORTEZ", 90},
        {"COX", 91},
        {"CRAIG", 92},
        {"CRAWFORD", 93},
        {"CROSS", 94},
        {"CRUZ", 95},
        {"CUMMINGS", 96},
        {"CUNNINGHAM", 97},
        {"CURRY", 98},
        {"CURTIS", 99},
        {"DANIEL", 100},
        {"DANIELS", 101},
        {"DAVIDSON", 102},
        {"DAVIS", 103},
        {"DAWSON", 104},
        {"DAY", 105},
        {"DEAN", 106},
        {"DELACRUZ", 107},
        {"DELEON", 108},
        {"DELGADO", 109},
        {"DENNIS", 110},
        {"DIAZ", 111},
        {"DIXON", 112},
        {"DOMINGUEZ", 113},
        {"DOUGLAS", 114},
        {"DOYLE", 115},
        {"DUNCAN", 116},
        {"DUNN", 117},
        {"DURAN", 118},
        {"EDWARDS", 119},
        {"ELLIOTT", 120},
        {"ELLIS", 121},
        {"ERICKSON", 122},
        {"ESPINOZA", 123},
        {"ESTRADA", 124},
        {"EVANS", 125},
        {"FARMER", 126},
        {"FERGUSON", 127},
        {"FERNANDEZ", 128},
        {"FIELDS", 129},
        {"FIGUEROA", 130},
        {"FISCHER", 131},
        {"FISHER", 132},
        {"FITZGERALD", 133},
        {"FLEMING", 134},
        {"FLETCHER", 135},
        {"FLORES", 136},
        {"FORD", 137},
        {"FOSTER", 138},
        {"FOWLER", 139},
        {"FOX", 140},
        {"FRANCIS", 141},
        {"FRANCO", 142},
        {"FRANK", 143},
        {"FRANKLIN", 144},
        {"FRAZIER", 145},
        {"FREEMAN", 146},
        {"FUENTES", 147},
        {"FULLER", 148},
        {"GALLAGHER", 149},
        {"GALLEGOS", 150},
        {"GARCIA", 151},
        {"GARDNER", 152},
        {"GARNER", 153},
        {"GARRETT", 154},
        {"GARZA", 155},
        {"GEORGE", 156},
        {"GIBSON", 157},
        {"GILBERT", 158},
        {"GILL", 159},
        {"GOMEZ", 160},
        {"GONZALES", 161},
        {"GONZALEZ", 162},
        {"GOODMAN", 163},
        {"GOODWIN", 164},
        {"GORDON", 165},
        {"GRAHAM", 166},
        {"GRANT", 167},
        {"GRAVES", 168},
        {"GRAY", 169},
        {"GREEN", 170},
        {"GREENE", 171},
        {"GREGORY", 172},
        {"GRIFFIN", 173},
        {"GRIFFITH", 174},
        {"GROSS", 175},
        {"GUERRA", 176},
        {"GUERRERO", 177},
        {"GUTIERREZ", 178},
        {"GUZMAN", 179},
        {"HAIL", 180},
        {"HALE", 181},
        {"HALL", 182},
        {"HAMILTON", 183},
        {"HAMMOND", 184},
        {"HAMPTON", 185},
        {"HANSEN", 186},
        {"HANSON", 187},
        {"HARDY", 188},
        {"HARMON", 189},
        {"HARPER", 190},
        {"HARRINGTON", 191},
        {"HARRIS", 192},
        {"HARRISON", 193},
        {"HART", 194},
        {"HARVEY", 195},
        {"HAWKINS", 196},
        {"HAYES", 197},
        {"HAYNES", 198},
        {"HENDERSON", 199},
        {"HENRY", 200},
        {"HERNANDEZ", 201},
        {"HERRERA", 202},
        {"HICKS", 203},
        {"HIGGINS", 204},
        {"HILL", 205},
        {"HINES", 206},
        {"HODGES", 207},
        {"HOFFMAN", 208},
        {"HOLLAND", 209},
        {"HOLMES", 210},
        {"HOLT", 211},
        {"HOPKINS", 212},
        {"HORTON", 213},
        {"HOWARD", 214},
        {"HOWELL", 215},
        {"HUANG", 216},
        {"HUBBARD", 217},
        {"HUDSON", 218},
        {"HUGHES", 219},
        {"HUNT", 220},
        {"HUNTER", 221},
        {"INGRAM", 222},
        {"JACKSON", 223},
        {"JACOBS", 224},
        {"JAMES", 225},
        {"JENKINS", 226},
        {"JENNINGS", 227},
        {"JENSEN", 228},
        {"JIMENEZ", 229},
        {"JOHNSON", 230},
        {"JOHNSTON", 231},
        {"JONES", 232},
        {"JORDAN", 233},
        {"JOSEPH", 234},
        {"JUAREZ", 235},
        {"KELLER", 236},
        {"KELLEY", 237},
        {"KELLY", 238},
        {"KENNEDY", 239},
        {"KHAN", 240},
        {"KIM", 241},
        {"KING", 242},
        {"KLEIN", 243},
        {"KNIGHT", 244},
        {"LAMBERT", 245},
        {"LANE", 246},
        {"LARA", 247},
        {"LARSON", 248},
        {"LAWRENCE", 249},
        {"LAWSON", 250},
        {"LE", 251},
        {"LEE", 252},
        {"LEON", 253},
        {"LEONARD", 254},
        {"LEWIS", 255},
        {"LI", 256},
        {"LIN", 257},
        {"LITTLE", 258},
        {"LIU", 259},
        {"LOGAN", 260},
        {"LONG", 261},
        {"LOPEZ", 262},
        {"LOVE", 263},
        {"LOWE", 264},
        {"LUCAS", 265},
        {"LUNA", 266},
        {"LYNCH", 267},
        {"LYONS", 268},
        {"MACK", 269},
        {"MALDONADO", 270},
        {"MALONE", 271},
        {"MANN", 272},
        {"MANNING", 273},
        {"MARQUEZ", 274},
        {"MARSHALL", 275},
        {"MARTIN", 276},
        {"MARTINEZ", 277},
        {"MASON", 278},
        {"MATTHEWS", 279},
        {"MAXWELL", 280},
        {"MAY", 281},
        {"MCCARTHY", 282},
        {"MCCOY", 283},
        {"MCDANIEL", 284},
        {"MCDONALD", 285},
        {"MCGEE", 286},
        {"MCKINNEY", 287},
        {"MCLAUGHLIN", 288},
        {"MEDINA", 289},
        {"MEJIA", 290},
        {"MENDEZ", 291},
        {"MENDOZA", 292},
        {"MEYER", 293},
        {"MILES", 294},
        {"MILLER", 295},
        {"MILLS", 296},
        {"MIRANDA", 297},
        {"MITCHELL", 298},
        {"MOLINA", 299},
        {"MONTGOMERY", 300},
        {"MONTOYA", 301},
        {"MOORE", 302},
        {"MORALES", 303},
        {"MORAN", 304},
        {"MORENO", 305},
        {"MORGAN", 306},
        {"MORRIS", 307},
        {"MORRISON", 308},
        {"MOSS", 309},
        {"MULLINS", 310},
        {"MUNOZ", 311},
        {"MURPHY", 312},
        {"MURRAY", 313},
        {"MYERS", 314},
        {"NAVARRO", 315},
        {"NEAL", 316},
        {"NELSON", 317},
        {"NEWMAN", 318},
        {"NEWTON", 319},
        {"NGUYEN", 320},
        {"NICHOLS", 321},
        {"NORMAN", 322},
        {"NORRIS", 323},
        {"NUNEZ", 324},
        {"OBRIEN", 325},
        {"OCHOA", 326},
        {"OCONNOR", 327},
        {"OLIVER", 328},
        {"OLSON", 329},
        {"ORTEGA", 330},
        {"ORTIZ", 331},
        {"OWENS", 332},
        {"PACHECO", 333},
        {"PADILLA", 334},
        {"PAGE", 335},
        {"PALMER", 336},
        {"PARK", 337},
        {"PARKER", 338},
        {"PARKS", 339},
        {"PARSONS", 340},
        {"PATEL", 341},
        {"PATTERSON", 342},
        {"PAUL", 343},
        {"PAYNE", 344},
        {"PEARSON", 345},
        {"PENA", 346},
        {"PEREZ", 347},
        {"PERKINS", 348},
        {"PERRY", 349},
        {"PERSON", 350},
        {"PETERS", 351},
        {"PETERSON", 352},
        {"PHAM", 353},
        {"PHILLIPS", 354},
        {"PIERCE", 355},
        {"PORTER", 356},
        {"POTTER", 357},
        {"POWELL", 358},
        {"POWERS", 359},
        {"PRICE", 360},
        {"QUINN", 361},
        {"RAMIREZ", 362},
        {"RAMOS", 363},
        {"RAMSEY", 364},
        {"RAY", 365},
        {"REED", 366},
        {"REESE", 367},
        {"REEVES", 368},
        {"REID", 369},
        {"REYES", 370},
        {"REYNOLDS", 371},
        {"RHODES", 372},
        {"RICE", 373},
        {"RICHARDS", 374},
        {"RICHARDSON", 375},
        {"RILEY", 376},
        {"RIOS", 377},
        {"RIVAS", 378},
        {"RIVERA", 379},
        {"ROBBINS", 380},
        {"ROBERTS", 381},
        {"ROBERTSON", 382},
        {"ROBINSON", 383},
        {"ROBLES", 384},
        {"RODGERS", 385},
        {"RODRIGUEZ", 386},
        {"ROGERS", 387},
        {"ROJAS", 388},
        {"ROMAN", 389},
        {"ROMERO", 390},
        {"ROSALES", 391},
        {"ROSE", 392},
        {"ROSS", 393},
        {"ROWE", 394},
        {"RUIZ", 395},
        {"RUSSELL", 396},
        {"RYAN", 397},
        {"SALAZAR", 398},
        {"SALINAS", 399},
        {"SANCHEZ", 400},
        {"SANDERS", 401},
        {"SANDOVAL", 402},
        {"SANTIAGO", 403},
        {"SANTOS", 404},
        {"SAUNDERS", 405},
        {"SCHMIDT", 406},
        {"SCHNEIDER", 407},
        {"SCHROEDER", 408},
        {"SCHULTZ", 409},
        {"SCHWARTZ", 410},
        {"SCOTT", 411},
        {"SERRANO", 412},
        {"SHARP", 413},
        {"SHAW", 414},
        {"SHELTON", 415},
        {"SHERMAN", 416},
        {"SILVA", 417},
        {"SIMMONS", 418},
        {"SIMON", 419},
        {"SIMPSON", 420},
        {"SIMS", 421},
        {"SINGH", 422},
        {"SMITH", 423},
        {"SNYDER", 424},
        {"SOLIS", 425},
        {"SOTO", 426},
        {"SPENCER", 427},
        {"STANLEY", 428},
        {"STEELE", 429},
        {"STEPHENS", 430},
        {"STEVENS", 431},
        {"STEVENSON", 432},
        {"STEWART", 433},
        {"STONE", 434},
        {"STRICKLAND", 435},
        {"SULLIVAN", 436},
        {"SUTTON", 437},
        {"SWANSON", 438},
        {"TATE", 439},
        {"TAYLOR", 440},
        {"TERRY", 441},
        {"THOMAS", 442},
        {"THOMPSON", 443},
        {"THORNTON", 444},
        {"TODD", 445},
        {"TORRES", 446},
        {"TOWNSEND", 447},
        {"TRAN", 448},
        {"TRUJILLO", 449},
        {"TUCKER", 450},
        {"TURNER", 451},
        {"VALDEZ", 452},
        {"VALENCIA", 453},
        {"VARGAS", 454},
        {"VASQUEZ", 455},
        {"VAUGHN", 456},
        {"VAZQUEZ", 457},
        {"VEGA", 458},
        {"VELASQUEZ", 459},
        {"WADE", 460},
        {"WAGNER", 461},
        {"WALKER", 462},
        {"WALLACE", 463},
        {"WALSH", 464},
        {"WALTERS", 465},
        {"WALTON", 466},
        {"WANG", 467},
        {"WARD", 468},
        {"WARNER", 469},
        {"WARREN", 470},
        {"WASHINGTON", 471},
        {"WATERS", 472},
        {"WATKINS", 473},
        {"WATSON", 474},
        {"WATTS", 475},
        {"WEAVER", 476},
        {"WEBB", 477},
        {"WEBER", 478},
        {"WEBSTER", 479},
        {"WELCH", 480},
        {"WELLS", 481},
        {"WEST", 482},
        {"WHEELER", 483},
        {"WHITE", 484},
        {"WILLIAMS", 485},
        {"WILLIAMSON", 486},
        {"WILLIS", 487},
        {"WILSON", 488},
        {"WISE", 489},
        {"WOLF", 490},
        {"WOLFE", 491},
        {"WONG", 492},
        {"WOOD", 493},
        {"WOODS", 494},
        {"WRIGHT", 495},
        {"WU", 496},
        {"YANG", 497},
        {"YOUNG", 498},
        {"ZHANG", 499},
        {"ZIMMERMAN", 500}
};

//Unordered map that stores unique hash value for each first name
unordered_map<string, long long> FirstMap = {
        {"AALIYAH", 1},
	{"AARON", 2},
	{"ABEL", 3},
	{"ABIGAIL", 4},
	{"ABRAHAM", 5},
	{"ADALINE", 6},
	{"ADALYN", 7},
	{"ADALYNN", 8},
	{"ADAM", 9},
	{"ADDISON", 10},
	{"ADELINE", 11},
	{"ADELYN", 12},
	{"ADRIAN", 13},
	{"ADRIANA", 14},
	{"AIDAN", 15},
	{"AIDEN", 16},
	{"ALAINA", 17},
	{"ALAN", 18},
	{"ALANA", 19},
	{"ALAYNA", 20},
	{"ALEJANDRO", 21},
	{"ALEX", 22},
	{"ALEXA", 23},
	{"ALEXANDER", 24},
	{"ALEXANDRA", 25},
	{"ALEXIS", 26},
	{"ALICE", 27},
	{"ALINA", 28},
	{"ALIVIA", 29},
	{"ALIYAH", 30},
 	{"ALLISON", 31},
	{"ALYSSA", 32},
	{"AMARA", 33},
	{"AMAYA", 34},
	{"AMELIA", 35},
	{"AMIR", 36},
	{"AMY", 37},
	{"ANA", 38},
	{"ANASTASIA", 39},
	{"ANDREA", 40},
	{"ANDRES", 41},
	{"ANDREW", 42},
	{"ANGEL", 43},
	{"ANGELA", 44},
	{"ANGELINA", 45},
	{"ANNA", 46},
	{"ANNABELLE", 47},
	{"ANTHONY", 48},
	{"ANTONIO", 49},
	{"ARABELLA", 50},
	{"ARIA", 51},
 	{"ARIANA", 52},
	{"ARIANNA", 53},
	{"ARIEL", 54},
	{"ARTHUR", 55},
	{"ARYA", 56},
	{"ASHER", 57},
	{"ASHLEY", 58},
	{"ASHTON", 59},
	{"ATHENA", 60},
	{"AUBREE", 61},
	{"AUBREY", 62},
	{"AUDREY", 63},
	{"AUGUST", 64},
	{"AURORA", 65},
	{"AUSTIN", 66},
	{"AUTUMN", 67},
	{"AVA", 68},
	{"AVERY", 69},
	{"AXEL", 70},
	{"AYDEN", 71},
	{"AYLA", 72},
	{"BAILEY", 73},
	{"BARRETT", 74},
	{"BEAU", 75},
	{"BECKETT", 76},
	{"BELLA", 77},
	{"BENJAMIN", 78},
	{"BENNETT", 79},
	{"BENTLEY", 80},
	{"BLAKE", 81},
	{"BRADLEY", 82},
	{"BRADY", 83},
	{"BRANDON", 84},
	{"BRANTLEY", 85},
	{"BRAXTON", 86},
	{"BRAYDEN", 87},
	{"BRIAN", 88},
	{"BRIANNA", 89},
	{"BRIELLE", 90},
	{"BRODY", 91},
	{"BROOKE", 92},
	{"BROOKLYN", 93},
	{"BROOKLYNN", 94},
	{"BROOKS", 95},
	{"BRYAN", 96},
	{"BRYCE", 97},
	{"BRYNLEE", 98},
	{"BRYSON", 99},
	{"CADEN", 100},
	{"CALEB", 101},
	{"CALLIE", 102},
	{"CALVIN", 103},
	{"CAMDEN", 104},
	{"CAMERON", 105},
	{"CAMILA", 106},
	{"CARLOS", 107},
	{"CAROLINE", 108},
	{"CARSON", 109},
	{"CARTER", 110},
	{"CATHERINE", 111},
	{"CAYDEN", 112},
	{"CECILIA", 113},
	{"CHARLES", 114},
	{"CHARLIE", 115},
	{"CHARLOTTE", 116},
	{"CHASE", 117},
	{"CHLOE", 118},
	{"CHRISTIAN", 119},
	{"CHRISTOPHER", 120},
	{"CLAIRE", 121},
	{"CLARA", 122},
	{"CLAYTON", 123},
	{"COLE", 124},
	{"COLIN", 125},
	{"COLTON", 126},
	{"CONNOR", 127},
	{"COOPER", 128},
	{"CORA", 129},
	{"DAISY", 130},
	{"DAKOTA", 131},
	{"DALEYZA", 132},
	{"DAMIAN", 133},
	{"DANIEL", 134},
	{"DANIELA", 135},
	{"DAVID", 136},
	{"DAWSON", 137},
	{"DEAN", 138},
	{"DECLAN", 139},
	{"DELANEY", 140},
	{"DELILAH", 141},
	{"DEREK", 142},
	{"DESTINY", 143},
	{"DIANA", 144},
	{"DIEGO", 145},
	{"DOMINIC", 146},
	{"DYLAN", 147},
	{"EASTON", 148},
	{"EDEN", 149},
	{"EDWARD", 150},
	{"ELEANOR", 151},
	{"ELENA", 152},
	{"ELI", 153},
	{"ELIANA", 154},
	{"ELIAS", 155},
	{"ELIJAH", 156},
	{"ELISE", 157},
	{"ELIZA", 158},
	{"ELIZABETH", 159},
	{"ELLA", 160},
	{"ELLIANA", 161},
	{"ELLIE", 162},
	{"ELLIOT", 163},
	{"ELLIOTT", 164},
	{"ELOISE", 165},
	{"EMERSON", 166},
	{"EMERSYN", 167},
	{"EMERY", 168},
	{"EMILIA", 169},
	{"EMILIANO", 170},
	{"EMILY", 171},
	{"EMMA", 172},
	{"EMMANUEL", 173},
	{"EMMETT", 174},
	{"ERIC", 175},
	{"ESTHER", 176},
	{"ETHAN", 177},
	{"EVA", 178},
	{"EVAN", 179},
	{"EVELYN", 180},
	{"EVERETT", 181},
	{"EVERLY", 182},
	{"EZEKIEL", 183},
	{"EZRA", 184},
	{"FAITH", 185},
	{"FELIX", 186},
	{"FINLEY", 187},
	{"FINN", 188},
	{"FIONA", 189},
	{"GABRIEL", 190},
	{"GABRIELLA", 191},
	{"GAEL", 192},
	{"GAVIN", 193},
	{"GENESIS", 194},
	{"GENEVIEVE", 195},
	{"GEORGE", 196},
	{"GEORGIA", 197},
	{"GIANNA", 198},
	{"GIOVANNI", 199},
	{"GRACE", 200},
	{"GRACIE", 201},
	{"GRAHAM", 202},
	{"GRANT", 203},
	{"GRAYSON", 204},
	{"GREYSON", 205},
	{"GRIFFIN", 206},
	{"HADLEY", 207},
	{"HAILEY", 208},
	{"HANNAH", 209},
	{"HARLEY", 210},
	{"HARMONY", 211},
	{"HARPER", 212},
	{"HARRISON", 213},
	{"HAYDEN", 214},
	{"HAZEL", 215},
	{"HENRY", 216},
	{"HOLDEN", 217},
	{"HUDSON", 218},
	{"HUNTER", 219},
	{"IAN", 220},
	{"IRIS", 221},
	{"ISAAC", 222},
	{"ISABEL", 223},
	{"ISABELLA", 224},
	{"ISABELLE", 225},
	{"ISAIAH", 226},
	{"ISLA", 227},
	{"ISRAEL", 228},
	{"IVAN", 229},
	{"IVY", 230},
	{"JACE", 231},
	{"JACK", 232},
	{"JACKSON", 233},
	{"JACOB", 234},
	{"JADE", 235},
	{"JADEN", 236},
	{"JAKE", 237},
	{"JAMES", 238},
	{"JAMESON", 239},
	{"JASMINE", 240},
	{"JASON", 241},
	{"JASPER", 242},
	{"JAVIER", 243},
	{"JAX", 244},
	{"JAXON", 245},
	{"JAXSON", 246},
	{"JAYCE", 247},
	{"JAYDEN", 248},
	{"JAYLA", 249},
	{"JEREMIAH", 250},
	{"JEREMY", 251},
	{"JESSE", 252},
	{"JESSICA", 253},
	{"JESUS", 254},
	{"JOANNA", 255},
	{"JOCELYN", 256},
	{"JOEL", 257},
	{"JOHN", 258},
	{"JONAH", 259},
	{"JONATHAN", 260},
	{"JORDAN", 261},
	{"JORDYN", 262},
	{"JORGE", 263},
	{"JOSE", 264},
	{"JOSEPH", 265},
	{"JOSEPHINE", 266},
	{"JOSHUA", 267},
	{"JOSIAH", 268},
	{"JOSIE", 269},
	{"JOSUE", 270},
	{"JUAN", 271},
	{"JUDAH", 272},
	{"JUDE", 273},
	{"JULIA", 274},
	{"JULIAN", 275},
	{"JULIANA", 276},
	{"JULIANNA", 277},
	{"JULIET", 278},
	{"JULIETTE", 279},
	{"JUNE", 280},
	{"JUSTIN", 281},
	{"KADEN", 282},
	{"KAI", 283},
	{"KAIDEN", 284},
	{"KALEB", 285},
	{"KARTER", 286},
	{"KATHERINE", 287},
	{"KAYDEN", 288},
	{"KAYLA", 289},
	{"KAYLEE", 290},
	{"KENDALL", 291},
	{"KENNEDY", 292},
	{"KENNETH", 293},
	{"KEVIN", 294},
	{"KHLOE", 295},
	{"KILLIAN", 296},
	{"KIMBERLY", 297},
	{"KING", 298},
	{"KINGSTON", 299},
	{"KINSLEY", 300},
	{"KNOX", 301},
	{"KYLE", 302},
	{"KYLIE", 303},
	{"KYRIE", 304},
	{"LAILA", 305},
	{"LANDON", 306},
	{"LAUREN", 307},
	{"LAYLA", 308},
	{"LEAH", 309},
	{"LEILA", 310},
	{"LEILANI", 311},
	{"LEO", 312},
	{"LEON", 313},
	{"LEONARDO", 314},
	{"LEVI", 315},
	{"LIAM", 316},
	{"LILA", 317},
	{"LILIANA", 318},
	{"LILLIAN", 319},
	{"LILLY", 320},
	{"LILY", 321},
	{"LINCOLN", 322},
	{"LOGAN", 323},
	{"LOLA", 324},
	{"LONDON", 325},
	{"LONDYN", 326},
	{"LORENZO", 327},
	{"LUCA", 328},
	{"LUCAS", 329},
	{"LUCIA", 330},
	{"LUCY", 331},
	{"LUIS", 332},
	{"LUKAS", 333},
	{"LUKE", 334},
	{"LUNA", 335},
	{"LYDIA", 336},
	{"LYLA", 337},
	{"MACKENZIE", 338},
	{"MADDOX", 339},
	{"MADELINE", 340},
	{"MADELYN", 341},
	{"MADISON", 342},
	{"MAGGIE", 343},
	{"MAKAYLA", 344},
	{"MALACHI", 345},
	{"MALIA", 346},
	{"MARCUS", 347},
	{"MARGARET", 348},
	{"MARIA", 349},
	{"MARIAH", 350},
	{"MARK", 351},
	{"MARLEY", 352},
	{"MARY", 353},
	{"MASON", 354},
	{"MATEO", 355},
	{"MATIAS", 356},
	{"MATTEO", 357},
	{"MATTHEW", 358},
	{"MAVERICK", 359},
	{"MAX", 360},
	{"MAXIMUS", 361},
	{"MAXWELL", 362},
	{"MAYA", 363},
	{"MCKENZIE", 364},
	{"MELANIE", 365},
	{"MELODY", 366},
	{"MESSIAH", 367},
	{"MIA", 368},
	{"MICAH", 369},
	{"MICHAEL", 370},
	{"MICHELLE", 371},
	{"MIGUEL", 372},
	{"MILA", 373},
	{"MILES", 374},
	{"MILO", 375},
	{"MOLLY", 376},
	{"MORGAN", 377},
	{"MYA", 378},
	{"MYLES", 379},
	{"NAOMI", 380},
	{"NATALIA", 381},
	{"NATALIE", 382},
	{"NATHAN", 383},
	{"NATHANIEL", 384},
	{"NEVAEH", 385},
	{"NICHOLAS", 386},
	{"NICOLAS", 387},
	{"NICOLE", 388},
	{"NOAH", 389},
	{"NOELLE", 390},
	{"NOLAN", 391},
	{"NORA", 392},
	{"NORAH", 393},
	{"NOVA", 394},
	{"OLIVER", 395},
	{"OLIVIA", 396},
	{"OMAR", 397},
	{"OSCAR", 398},
	{"OWEN", 399},
	{"PAIGE", 400},
	{"PAISLEY", 401},
	{"PARKER", 402},
	{"PATRICK", 403},
	{"PAUL", 404},
	{"PAXTON", 405},
	{"PAYTON", 406},
	{"PENELOPE", 407},
	{"PETER", 408},
	{"PEYTON", 409},
	{"PIPER", 410},
	{"PRESLEY", 411},
	{"PRESTON", 412},
	{"QUINN", 413},
	{"RACHEL", 414},
	{"RAELYNN", 415},
	{"REAGAN", 416},
	{"REBECCA", 417},
	{"REESE", 418},
	{"REMI", 419},
	{"REMINGTON", 420},
	{"RHETT", 421},
	{"RICHARD", 422},
	{"RILEY", 423},
	{"RIVER", 424},
	{"ROBERT", 425},
	{"ROMAN", 426},
	{"ROSALIE", 427},
	{"ROSE", 428},
	{"ROWAN", 429},
	{"RUBY", 430},
	{"RYAN", 431},
	{"RYDER", 432},
	{"RYKER", 433},
	{"RYLEE", 434},
	{"RYLEIGH", 435},
	{"SADIE", 436},
	{"SAMANTHA", 437},
	{"SAMUEL", 438},
	{"SANTIAGO", 439},
	{"SARA", 440},
	{"SARAH", 441},
	{"SAVANNAH", 442},
	{"SAWYER", 443},
	{"SCARLETT", 444},
	{"SEBASTIAN", 445},
	{"SELENA", 446},
	{"SERENITY", 447},
	{"SIENNA", 448},
	{"SILAS", 449},
	{"SKYLAR", 450},
	{"SLOANE", 451},
	{"SOFIA", 452},
	{"SOPHIA", 453},
	{"SOPHIE", 454},
	{"STELLA", 455},
	{"STEVEN", 456},
	{"SUMMER", 457},
	{"SYDNEY", 458},
	{"TAYLOR", 459},
	{"TEAGAN", 460},
	{"TESSA", 461},
	{"THEODORE", 462},
	{"THIAGO", 463},
	{"THOMAS", 464},
	{"TIMOTHY", 465},
	{"TRINITY", 466},
	{"TRISTAN", 467},
	{"TUCKER", 468},
	{"TYLER", 469},
	{"VALENTINA", 470},
	{"VALERIA", 471},
	{"VALERIE", 472},
	{"VANESSA", 473},
	{"VICTOR", 474},
	{"VICTORIA", 475},
	{"VINCENT", 476},
	{"VIOLET", 477},
	{"VIVIAN", 478},
	{"WAYLON", 479},
	{"WESLEY", 480},
	{"WESTON", 481},
	{"WILLIAM", 482},
	{"WILLOW", 483},
	{"WYATT", 484},
	{"XANDER", 485},
	{"XAVIER", 486},
	{"XIMENA", 487},
	{"ZACHARY", 488},
	{"ZANDER", 489},
	{"ZANE", 490},
	{"ZAYDEN", 491},
	{"ZION", 492},
	{"ZOE", 493},
	{"ZOEY", 494}
};

//Declaration of array of Pointers to members of the list
Data* arrayPointers[1200000];
int listSize;

//Declaration of arrays for radix sort
Data* cup[100000][500];
int cupCount[100000] = {0};

//Simple structure that stores unique id for each person and a pointer to that member of the list
struct People {
        unsigned long long id;
        Data* person;
};

//Declaration of array of simple structures
People arrayNames[1200000];

//Function used to convert the SSN from a string to a long long
long long ssntol(string ssn) {
        return (100000000*(ssn.at(0) - 48) + 10000000*(ssn.at(1) - 48) + 1000000*(ssn.at(2) - 48) + 100000*(ssn.at(4) - 48) + 10000*(ssn.at(5) - 48) + 1000*(ssn.at(7) - 48) + 100*(ssn.at(8) - 48) + 10*(ssn.at(9) - 48) + 1*(ssn.at(10) - 48));
}

//Function used to convert the SSN from a string to an int
int ssntoi(int l, string ssn) {
        if(l == 4) {
                return (1000*(ssn.at(0) - 48) + 100*(ssn.at(1) - 48) + 10*(ssn.at(2) - 48) + 1*(ssn.at(4) - 48));
        }
        else if(l == 5) {
                return (10000*(ssn.at(5) - 48) + 1000*(ssn.at(7) - 48) + 100*(ssn.at(8) - 48) + 10*(ssn.at(9) - 48) + 1*(ssn.at(10) - 48));
        }
        else {
                return (100000000*(ssn.at(0) - 48) + 10000000*(ssn.at(1) - 48) + 1000000*(ssn.at(2) - 48) + 100000*(ssn.at(4) - 48) + 10000*(ssn.at(5) - 48) + 1000*(ssn.at(7) - 48) + 100*(ssn.at(8) - 48) + 10*(ssn.at(9) - 48) + 1*(ssn.at(10) - 48));
        }
}

//Radix sort function used to sort T4
void radix_sort() {
        int last5ssn =  0;

        //For loop puts the pointer containing the SSN into cups
        for(int i = 0; i < listSize; i++) {
                last5ssn = ssntoi(5, arrayPointers[i]->ssn);
                cup[last5ssn][cupCount[last5ssn]] = arrayPointers[i];
                cupCount[last5ssn] += 1;
        }
        int a = 0;
        int b = 0;

        //For loop that organizes the array of pointers
        for(int i = 0; i < listSize; i++) {
                if(b == cupCount[a]) {
                        b = 0;
                        a += 1;
                        i -= 1;
                }
                else {
                        arrayPointers[i] = cup[a][b];
                        b += 1;
                }
        }

        //For loop that clears the cupCount array
        for(int i = 0; i < 100000; i++) {
                cupCount[i] = 0;
        }

        int first4ssn = 0;

        //For loop puts the pointer containing the SSN into cups
        for(int i = 0; i < listSize; i++) {
                first4ssn = ssntoi(4, arrayPointers[i]->ssn);
                cup[first4ssn][cupCount[first4ssn]] = arrayPointers[i];
                cupCount[first4ssn] +=1;
        }
        a = 0;
        b = 0;

        //For loop that organizes that array of pointers
        for(int i = 0; i < listSize; i++) {
                if(b == cupCount[a]) {
                        b = 0;
                        a += 1;
                        i -= 1;
                }
                else {
                        arrayPointers[i] = cup[a][b];
                        b += 1;
                }
        }
}

//Insertion sort used to sort T3
void insertion_sort() {
        int count = 1;
        for(int i = 1; i < listSize; i++) {
                if(arrayPointers[i]->lastName != arrayPointers[i - 1]->lastName || arrayPointers[i]->firstName != arrayPointers[i - 1]->firstName) {
                        count = 0;
                }
                Data* key = arrayPointers[i];
                int j = i;
                while(j > (i - count) && ssntoi(0, arrayPointers[j - 1]->ssn) > ssntoi(0, key->ssn)) {
                        arrayPointers[j] = arrayPointers[j - 1];
                        j -= 1;
                }
                arrayPointers[j] = key;
                count += 1;
        }
}

//Simple boolean function used to determine sort order for standard C sort
bool comparePeople(People a, People b) {
        return (a.id < b.id);
}

//Function that sorts the inputted list
void sortDataList(list<Data *> &l) {
        listSize = l.size();
        auto it = l.begin();
        int test;

        //For loop to create an array of pointers to the objects in the list
        for(int i = 0; i < listSize; i++) {
                arrayPointers[i] = (*it++);
        }

        //If statement used to sort T1
        if(listSize < 200000) {
                it = l.begin();

                //For loop to create an array of structures
                for(int i = 0; i < listSize; i++) {
                        arrayNames[i].person = (*it++);
                        arrayNames[i].id = 1000000000000*LastMap[arrayPointers[i]->lastName] + 1000000000*FirstMap[arrayPointers[i]->firstName] + ssntol(arrayPointers[i]->ssn);
                }
                sort(arrayNames, arrayNames + listSize, comparePeople);
                test = 1;
        }
        //Else if statement used to sort T3
        else if(arrayPointers[0]->lastName == arrayPointers[1]->lastName && arrayPointers[0]->firstName == arrayPointers[1]->firstName && arrayPointers[0]->lastName != arrayPointers[listSize - 1]->lastName) {
                insertion_sort();
                test = 3;
        }
        //Else if statement used to sort T4
        else if(arrayPointers[0]->lastName == arrayPointers[listSize - 1]->lastName && arrayPointers[0]->firstName == arrayPointers[listSize - 1]->firstName) {
                radix_sort();
                test = 4;
        }
        //Else statement used to sort T2
        else {
                it = l.begin();

                //For loop to create an array of structures
                for(int i = 0; i < listSize; i++) {
                        arrayNames[i].person = (*it++);
                        arrayNames[i].id = 1000000000000*LastMap[arrayPointers[i]->lastName] + 1000000000*FirstMap[arrayPointers[i]->firstName] + ssntol(arrayPointers[i]->ssn);
                }
                sort(arrayNames, arrayNames + listSize, comparePeople);
                test = 2;
        }

        it = l.begin();

        //If statement to ensure that the right array gets transferred back to the list
        if(test == 1 || test ==2) {
                for(int j = 0; j < listSize; j++) {
                        (*it++) = arrayNames[j].person;
                }
        }
        else {
                for(int j = 0; j < listSize; j++) {
                        (*it++) = arrayPointers[j];
                }
        }
}
