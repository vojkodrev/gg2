<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.11" tiledversion="1.12.1" name="texture" tilewidth="64" tileheight="64" tilecount="322" columns="14" objectalignment="topleft" tilerendersize="grid" fillmode="preserve-aspect-fit">
 <image source="../texture/texture.png" width="896" height="1472"/>
 <tile id="6">
  <properties>
   <property name="ammo" value="arrow1"/>
   <property name="facing" value="right"/>
   <property name="weapon" value="bow1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collision" x="16.2675" y="38.405" width="31.5205" height="18.25"/>
   <object id="2" name="anchor" x="35.6864" y="38.5131" width="10.1288" height="9.65771"/>
  </objectgroup>
 </tile>
 <tile id="20">
  <properties>
   <property name="AI" type="int" value="1"/>
   <property name="facing" value="left"/>
   <property name="patrol01" value="-50,-50"/>
   <property name="patrol02" value="70,-75"/>
   <property name="patrol03" value="70,75"/>
   <property name="patrol04" value="-70,70"/>
   <property name="patrolCount" type="int" value="4"/>
   <property name="weapon" value="staff1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collision" x="18.1711" y="44.0307" width="31.5" height="13.1769"/>
   <object id="2" name="anchor" x="18.7265" y="44.5197" width="7.18439" height="6.59551"/>
  </objectgroup>
 </tile>
 <tile id="34">
  <properties>
   <property name="AI" type="int" value="1"/>
   <property name="facing" value="left"/>
   <property name="patrol01" value="-50,-50"/>
   <property name="patrol02" value="70,-75"/>
   <property name="patrol03" value="70,75"/>
   <property name="patrol04" value="-70,100"/>
   <property name="patrolCount" type="int" value="4"/>
   <property name="weapon" value="sword1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collision" x="18.0117" y="38.4795" width="30.8772" height="18.3626"/>
   <object id="2" name="anchor" x="18.8443" y="39.102" width="9.77549" height="8.95105"/>
  </objectgroup>
 </tile>
 <tile id="38">
  <objectgroup draworder="index" id="2">
   <object id="1" name="collision" x="10.75" y="29.5" width="29.75" height="18.5"/>
  </objectgroup>
 </tile>
 <tile id="48">
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
 <tile id="58">
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
 <tile id="98">
  <properties>
   <property name="AI" type="int" value="2"/>
   <property name="facing" value="right"/>
  </properties>
  <objectgroup draworder="index" id="3">
   <object id="3" name="collision" x="16.6667" y="40.6667" width="33.6667" height="15.6667"/>
  </objectgroup>
 </tile>
 <tile id="112">
  <objectgroup draworder="index" id="3">
   <object id="3" name="collision" x="5.49708" y="44.6784" width="52.5146" height="19.4152"/>
  </objectgroup>
  <animation>
   <frame tileid="112" duration="100"/>
   <frame tileid="113" duration="100"/>
   <frame tileid="114" duration="100"/>
   <frame tileid="115" duration="100"/>
   <frame tileid="116" duration="100"/>
   <frame tileid="117" duration="100"/>
   <frame tileid="118" duration="100"/>
   <frame tileid="119" duration="100"/>
   <frame tileid="120" duration="100"/>
   <frame tileid="121" duration="100"/>
   <frame tileid="122" duration="100"/>
   <frame tileid="123" duration="100"/>
  </animation>
 </tile>
 <tile id="169">
  <properties>
   <property name="animationAngleStart" type="float" value="-20"/>
   <property name="animationAngleStop" type="float" value="110"/>
   <property name="animationTime" type="float" value="250"/>
   <property name="facing" value="right"/>
   <property name="initialAngle" type="float" value="45"/>
   <property name="scale" type="float" value="1.2"/>
   <property name="type" value="polearm1"/>
  </properties>
  <objectgroup draworder="index" id="3">
   <object id="2" name="collision" x="32.9775" y="4.23997" width="27.0887" height="26.9709"/>
   <object id="3" name="anchor" x="12.3666" y="44.9908" width="5.88885" height="6.59551"/>
  </objectgroup>
 </tile>
 <tile id="170">
  <properties>
   <property name="facing" value="right"/>
   <property name="scale" type="float" value="1"/>
   <property name="type" value="staff1"/>
  </properties>
  <objectgroup draworder="index" id="4">
   <object id="4" name="anchor" x="18.491" y="40.6331" width="5.29996" height="5.18219"/>
  </objectgroup>
 </tile>
 <tile id="188">
  <properties>
   <property name="rotate" type="float" value="45"/>
   <property name="scale" type="float" value="1"/>
   <property name="type" value="arrow1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="anchor" x="10.1847" y="50.8033" width="5.53552" height="5.18219"/>
  </objectgroup>
 </tile>
 <tile id="227">
  <properties>
   <property name="rotate" type="float" value="-135"/>
   <property name="scale" type="float" value="1"/>
   <property name="type" value="bow1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="anchor" x="32.1179" y="2.73405" width="13.4266" height="14.6043"/>
   <object id="2" name="ammoAnchor" x="30.4357" y="22.4772" width="9.78674" height="9.57164"/>
  </objectgroup>
 </tile>
 <tile id="253">
  <properties>
   <property name="facing" value="right"/>
   <property name="scale" type="float" value="1"/>
   <property name="type" value="sword1"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collision" x="21.0821" y="6.00662" width="38.5131" height="37.3353"/>
   <object id="2" name="anchor" x="11.3066" y="46.8752" width="4.12219" height="6.83106"/>
  </objectgroup>
 </tile>
</tileset>
