PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//1940129/764789/2.50/18/3/Connector

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r80_30"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.300) (shapeHeight 0.800))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(padStyleDef "r80_40"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.400) (shapeHeight 0.800))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "AYF531635" (originalName "AYF531635")
		(multiLayer
			(pad (padNum 1) (padStyleRef r80_30) (pt -3.750, 1.440) (rotation 0))
			(pad (padNum 2) (padStyleRef r80_30) (pt -3.250, 1.440) (rotation 0))
			(pad (padNum 3) (padStyleRef r80_30) (pt -2.750, 1.440) (rotation 0))
			(pad (padNum 4) (padStyleRef r80_30) (pt -2.250, 1.440) (rotation 0))
			(pad (padNum 5) (padStyleRef r80_30) (pt -1.750, 1.440) (rotation 0))
			(pad (padNum 6) (padStyleRef r80_30) (pt -1.250, 1.440) (rotation 0))
			(pad (padNum 7) (padStyleRef r80_30) (pt -0.750, 1.440) (rotation 0))
			(pad (padNum 8) (padStyleRef r80_30) (pt -0.250, 1.440) (rotation 0))
			(pad (padNum 9) (padStyleRef r80_30) (pt 0.250, 1.440) (rotation 0))
			(pad (padNum 10) (padStyleRef r80_30) (pt 0.750, 1.440) (rotation 0))
			(pad (padNum 11) (padStyleRef r80_30) (pt 1.250, 1.440) (rotation 0))
			(pad (padNum 12) (padStyleRef r80_30) (pt 1.750, 1.440) (rotation 0))
			(pad (padNum 13) (padStyleRef r80_30) (pt 2.250, 1.440) (rotation 0))
			(pad (padNum 14) (padStyleRef r80_30) (pt 2.750, 1.440) (rotation 0))
			(pad (padNum 15) (padStyleRef r80_30) (pt 3.250, 1.440) (rotation 0))
			(pad (padNum 16) (padStyleRef r80_30) (pt 3.750, 1.440) (rotation 0))
			(pad (padNum 17) (padStyleRef r80_40) (pt -4.750, -1.060) (rotation 0))
			(pad (padNum 18) (padStyleRef r80_40) (pt 4.750, -1.060) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0.000, 0.120) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -5 1.6) (pt 5 1.6) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 5 1.6) (pt 5 -1.6) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 5 -1.6) (pt -5 -1.6) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -5 -1.6) (pt -5 1.6) (width 0.025))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -6 2.84) (pt 6 2.84) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 6 2.84) (pt 6 -2.6) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 6 -2.6) (pt -6 -2.6) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -6 -2.6) (pt -6 2.84) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -4.2 1.6) (pt -5 1.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -5 1.6) (pt -5 -0.4) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -4.2 -1.6) (pt 4.2 -1.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 5 -0.4) (pt 5 1.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 5 1.6) (pt 4.2 1.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.75 2.4) (pt -3.75 2.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -3.75, 2.35) (radius 0.05) (startAngle 90.0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.75 2.3) (pt -3.75 2.3) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -3.75, 2.35) (radius 0.05) (startAngle 270) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "AYF531635" (originalName "AYF531635")

		(pin (pinNum 1) (pt 1000 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 1000 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 1000 mils -200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 1000 mils -300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -325 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 5) (pt 1000 mils -400 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -425 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 6) (pt 1000 mils -500 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -525 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 7) (pt 1000 mils -600 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -625 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 8) (pt 1000 mils -700 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -725 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 9) (pt 1000 mils -800 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -825 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 10) (pt 1000 mils -900 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -925 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 11) (pt 1000 mils -1000 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1025 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 12) (pt 1000 mils -1100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 13) (pt 1000 mils -1200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 14) (pt 1000 mils -1300 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1325 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 15) (pt 1000 mils -1400 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1425 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 16) (pt 1000 mils -1500 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -1525 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 17) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 18) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 800 mils 100 mils) (width 6 mils))
		(line (pt 800 mils 100 mils) (pt 800 mils -1600 mils) (width 6 mils))
		(line (pt 800 mils -1600 mils) (pt 200 mils -1600 mils) (width 6 mils))
		(line (pt 200 mils -1600 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 850 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 850 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "AYF531635" (originalName "AYF531635") (compHeader (numPins 18) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "4") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "5" (pinName "5") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "6" (pinName "6") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "7" (pinName "7") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "8" (pinName "8") (partNum 1) (symPinNum 8) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "9" (pinName "9") (partNum 1) (symPinNum 9) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "10" (pinName "10") (partNum 1) (symPinNum 10) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "11" (pinName "11") (partNum 1) (symPinNum 11) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "12" (pinName "12") (partNum 1) (symPinNum 12) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "13" (pinName "13") (partNum 1) (symPinNum 13) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "14" (pinName "14") (partNum 1) (symPinNum 14) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "15" (pinName "15") (partNum 1) (symPinNum 15) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "16" (pinName "16") (partNum 1) (symPinNum 16) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "MP1" (pinName "MP1") (partNum 1) (symPinNum 17) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "MP2" (pinName "MP2") (partNum 1) (symPinNum 18) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "AYF531635"))
		(attachedPattern (patternNum 1) (patternName "AYF531635")
			(numPads 18)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
				(padNum 6) (compPinRef "6")
				(padNum 7) (compPinRef "7")
				(padNum 8) (compPinRef "8")
				(padNum 9) (compPinRef "9")
				(padNum 10) (compPinRef "10")
				(padNum 11) (compPinRef "11")
				(padNum 12) (compPinRef "12")
				(padNum 13) (compPinRef "13")
				(padNum 14) (compPinRef "14")
				(padNum 15) (compPinRef "15")
				(padNum 16) (compPinRef "16")
				(padNum 17) (compPinRef "MP1")
				(padNum 18) (compPinRef "MP2")
			)
		)
		(attr "Mouser Part Number" "769-AYF531635")
		(attr "Mouser Price/Stock" "https://www.mouser.com/Search/Refine.aspx?Keyword=769-AYF531635")
		(attr "Manufacturer_Name" "Panasonic")
		(attr "Manufacturer_Part_Number" "AYF531635")
		(attr "Description" "Panasonic Y5B 0.5mm Pitch 16 Way SMT Female FPC Connector")
		(attr "<Hyperlink>" "https://componentsearchengine.com/Datasheets/1/AYF531635.pdf")
		(attr "<Component Height>" "2.06")
		(attr "<STEP Filename>" "AYF531635.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
