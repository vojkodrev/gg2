<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.11" tiledversion="1.12.1" name="texture" tilewidth="64" tileheight="64" tilecount="108" columns="12" objectalignment="topleft" tilerendersize="grid" fillmode="preserve-aspect-fit">
 <image source="../texture/texture.png" width="768" height="576"/>
 <tile id="6">
  <properties>
   <property name="facing" value="right"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" x="16.2675" y="38.405" width="31.5205" height="18.25"/>
  </objectgroup>
 </tile>
 <tile id="18">
  <properties>
   <property name="AI" type="int" value="1"/>
   <property name="facing" value="left"/>
   <property name="patrol01" value="-50,-50"/>
   <property name="patrol02" value="70,-75"/>
   <property name="patrol03" value="70,75"/>
   <property name="patrol04" value="-70,70"/>
   <property name="patrolCount" type="int" value="4"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" x="18.1711" y="44.0307" width="31.5" height="13.1769"/>
  </objectgroup>
 </tile>
 <tile id="30">
  <properties>
   <property name="AI" type="int" value="1"/>
   <property name="facing" value="left"/>
   <property name="patrol01" value="-50,-50"/>
   <property name="patrol02" value="70,-75"/>
   <property name="patrol03" value="70,75"/>
   <property name="patrol04" value="-70,100"/>
   <property name="patrolCount" type="int" value="4"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" x="18.0117" y="38.4795" width="30.8772" height="18.3626"/>
  </objectgroup>
 </tile>
 <tile id="34">
  <objectgroup draworder="index" id="2">
   <object id="1" x="10.75" y="29.5" width="29.75" height="18.5"/>
  </objectgroup>
 </tile>
 <tile id="42">
  <properties>
   <property name="colH" type="int" value="26"/>
   <property name="colOffX" type="int" value="126"/>
   <property name="colOffY" type="int" value="324"/>
   <property name="colW" type="int" value="28"/>
   <property name="h" type="int" value="350"/>
   <property name="type" value="marker"/>
   <property name="w" type="int" value="285"/>
   <property name="x" type="int" value="465"/>
   <property name="y" type="int" value="17"/>
  </properties>
 </tile>
 <tile id="50">
  <properties>
   <property name="colH" type="int" value="51"/>
   <property name="colOffX" type="int" value="0"/>
   <property name="colOffY" type="int" value="93"/>
   <property name="colW" type="int" value="74"/>
   <property name="h" type="int" value="144"/>
   <property name="scale" type="float" value="1"/>
   <property name="type" value="marker"/>
   <property name="w" type="int" value="74"/>
   <property name="x" type="int" value="27"/>
   <property name="y" type="int" value="280"/>
  </properties>
 </tile>
 <tile id="96">
  <objectgroup draworder="index" id="3">
   <object id="3" x="5.49708" y="44.6784" width="52.5146" height="19.4152"/>
  </objectgroup>
  <animation>
   <frame tileid="96" duration="100"/>
   <frame tileid="97" duration="100"/>
   <frame tileid="98" duration="100"/>
   <frame tileid="99" duration="100"/>
   <frame tileid="100" duration="100"/>
   <frame tileid="101" duration="100"/>
   <frame tileid="102" duration="100"/>
   <frame tileid="103" duration="100"/>
   <frame tileid="104" duration="100"/>
   <frame tileid="105" duration="100"/>
   <frame tileid="106" duration="100"/>
   <frame tileid="107" duration="100"/>
  </animation>
 </tile>
</tileset>
