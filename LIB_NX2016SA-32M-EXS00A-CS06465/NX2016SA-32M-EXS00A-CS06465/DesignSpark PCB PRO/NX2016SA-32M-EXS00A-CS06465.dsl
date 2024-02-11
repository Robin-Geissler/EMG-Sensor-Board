SamacSys ECAD Model
1015721/764789/2.50/4/0/Crystal or Oscillator

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r85_75"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.750) (shapeHeight 0.850))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "NX2016SA32MEXS00ACS06465" (originalName "NX2016SA32MEXS00ACS06465")
		(multiLayer
			(pad (padNum 1) (padStyleRef r85_75) (pt -0.675, -0.525) (rotation 90))
			(pad (padNum 2) (padStyleRef r85_75) (pt 0.675, -0.525) (rotation 90))
			(pad (padNum 3) (padStyleRef r85_75) (pt 0.675, 0.525) (rotation 90))
			(pad (padNum 4) (padStyleRef r85_75) (pt -0.675, 0.525) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt -0.000, 0.000) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 0.8) (pt 1 0.8) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 0.8) (pt 1 -0.8) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 -0.8) (pt -1 -0.8) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 -0.8) (pt -1 0.8) (width 0.2))
		)
		(layerContents (layerNumRef 30)
			(line (pt -2.1 1.9) (pt 2.1 1.9) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 2.1 1.9) (pt 2.1 -1.9) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 2.1 -1.9) (pt -2.1 -1.9) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -2.1 -1.9) (pt -2.1 1.9) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.8 -1.4) (pt -0.8 -1.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -0.75, -1.4) (radius 0.05) (startAngle 180.0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.7 -1.4) (pt -0.7 -1.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -0.75, -1.4) (radius 0.05) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "NX2016SA-32M-EXS00A-CS06465" (originalName "NX2016SA-32M-EXS00A-CS06465")

		(pin (pinNum 1) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 1600 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1370 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 1600 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1370 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 4) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 1400 mils 100 mils) (width 6 mils))
		(line (pt 1400 mils 100 mils) (pt 1400 mils -200 mils) (width 6 mils))
		(line (pt 1400 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1450 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "NX2016SA-32M-EXS00A-CS06465" (originalName "NX2016SA-32M-EXS00A-CS06465") (compHeader (numPins 4) (numParts 1) (refDesPrefix Y)
		)
		(compPin "1" (pinName "CRYSTAL_1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "GND_1") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "CRYSTAL_2") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "4" (pinName "GND_2") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "NX2016SA-32M-EXS00A-CS06465"))
		(attachedPattern (patternNum 1) (patternName "NX2016SA32MEXS00ACS06465")
			(numPads 4)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
			)
		)
		(attr "Manufacturer_Name" "NDK")
		(attr "Manufacturer_Part_Number" "NX2016SA-32M-EXS00A-CS06465")
		(attr "Mouser Part Number" "344-NX2016SA32S06465")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/NDK/NX2016SA-32M-EXS00A-CS06465?qs=w%2Fv1CP2dgqr82b0JjRnv4A%3D%3D")
		(attr "Arrow Part Number" "")
		(attr "Arrow Price/Stock" "")
		(attr "Description" "CRYSTAL 32MHZ 10PF SMD")
		(attr "Datasheet Link" "http://www.ndk.com/images/products/catalog/c_NX2016SA_e.pdf")
		(attr "Height" "0.5 mm")
	)

)
