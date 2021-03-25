// Greg Talotta lab 9
char *bigstring = "Exxon Valdez at Prince William Sound in 1989 \nHistory \nName:        Oriental Nicety \nOwner:         \nHong Kong Bloom Shipping Ltd. (2008–2012) \nSeaRiver Maritime (1989–2008) \nExxon (1986–1989) \nPort of registry:         \n Panama (2008–2012) \n Marshall Islands (2005–2008) \n United States (1986–2005) \nOrdered:        1 August 1984 \nBuilder:         \nNational Steel and Shipbuilding Company \nSan Diego, California \nLaid down:        24 July 1985 \nLaunched:        14 October 1986 \nIn service:        11 December 1986-20 March 2012 \nOut of service:        21 March 2012 (sold for scrap) \nRenamed:         \nExxon Valdez (1986–1989) \nExxon Mediterranean (1990–1993) \nSea River Mediterranean (1993–2005) \nS/R Mediterranean (1993–2005) \nMediterranean (2005–2008) \nDong Fang Ocean (2008–2011) \nOriental Nicety (2011–2012) \nRefit:        30 June 1989 \nIdentification:         \nMaritime call sign: 3EPL6 \nIMO number: 8414520 \nMMSI number: 356270000 \nFate:        Beached for dismantling 2 August, 2012 \nNotes:        [1][2] \nGeneral characteristics \nClass and type:        VLCC oil tanker \nType:        ABS: A1, ore carrier, AMS, ACCU, GRAB 25 \nTonnage:        214,861 DWT[3] \nDisplacement:        240,291 long tons[3] \nLength:        987 ft (301 m) overall[3] \nBeam:        166 ft (51 m)[3] \nDraft:        64.5 ft (19.7 m)[3] \nDepth:        88 ft (27 m)[3] \nInstalled power:        31,650 bhp (23,600 kW) at 79 rpm \nPropulsion:        Eight-cylinder, reversible, slow-speed Sulzer marine diesel engine \nSpeed:        16.25 knots (30.10 km/h; 18.70 mph) \nCapacity:        1.48 million barrels (235,000 m³) of crude oil[3] \nCrew:        21 \nNotes:        was an oil tanker that gained notoriety after running aground in Prince William Sound spilling hundreds of thousands of barrels of crude oil in Alaska. On March 24, 1989, while owned by the former Exxon Shipping Company, and captained by Joseph Hazelwood and First Mate James Kunkel[5] bound for Long Beach, California, the vessel ran aground on the Bligh Reef resulting in the second largest oil spill in United States history.[6] The size of the spill is estimated to have been 40,900 to 120,000 m3 (10,800,000 to 31,700,000 US gal), or 257,000 to 750,000 barrels.[7][8] In 1989, the Exxon Valdez oil spill was listed as the 54th largest spill in history.[citation needed] \n \n";

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(bigstring);
  delay(300);
}
