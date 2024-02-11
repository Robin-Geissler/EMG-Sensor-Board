SamacSys ECAD Model
1645012/764789/2.50/4/2/Filter

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r70_27.5"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.275) (shapeHeight 0.700))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(padStyleDef "r45_24.5"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.245) (shapeHeight 0.450))
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
	(patternDef "DLF162500LT5028A1" (originalName "DLF162500LT5028A1")
		(multiLayer
			(pad (padNum 1) (padStyleRef r70_27.5) (pt -0.612, 0.000) (rotation 0))
			(pad (padNum 2) (padStyleRef r45_24.5) (pt 0.000, -0.227) (rotation 90))
			(pad (padNum 3) (padStyleRef r70_27.5) (pt 0.613, 0.000) (rotation 0))
			(pad (padNum 4) (padStyleRef r45_24.5) (pt 0.000, 0.227) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt -0.250, 0.000) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 -0.4) (pt 0.8 -0.4) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 -0.4) (pt 0.8 0.4) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 0.4) (pt -0.8 0.4) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 0.4) (pt -0.8 -0.4) (width 0.2))
		)
		(layerContents (layerNumRef 30)
			(line (pt -2.3 -1.4) (pt 1.8 -1.4) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.8 -1.4) (pt 1.8 1.4) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.8 1.4) (pt -2.3 1.4) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -2.3 1.4) (pt -2.3 -1.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.3 0.1) (pt -1.3 0.1) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -1.25, 0.1) (radius 0.05) (startAngle 180.0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.2 0.1) (pt -1.2 0.1) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -1.25, 0.1) (radius 0.05) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "DLF162500LT-5028A1" (originalName "DLF162500LT-5028A1")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 500 mils -700 mils) (rotation 90) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 525 mils -470 mils) (rotation 90]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 1000 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 4) (pt 500 mils 700 mils) (rotation 270) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 525 mils 470 mils) (rotation 90]) (justify "Right") (textStyleRef "Default"))
		))
		(line (pt 200 mils 500 mils) (pt 800 mils 500 mils) (width 6 mils))
		(line (pt 800 mils 500 mils) (pt 800 mils -500 mils) (width 6 mils))
		(line (pt 800 mils -500 mils) (pt 200 mils -500 mils) (width 6 mils))
		(line (pt 200 mils -500 mils) (pt 200 mils 500 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 850 mils 700 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "DLF162500LT-5028A1" (originalName "DLF162500LT-5028A1") (compHeader (numPins 4) (numParts 1) (refDesPrefix FL)
		)
		(compPin "1" (pinName "IN") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "GND_1") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "OUT") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "4" (pinName "GND_2") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "DLF162500LT-5028A1"))
		(attachedPattern (patternNum 1) (patternName "DLF162500LT5028A1")
			(numPads 4)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
			)
		)
		(attr "Manufacturer_Name" "TDK")
		(attr "Manufacturer_Part_Number" "DLF162500LT-5028A1")
		(attr "Mouser Part Number" "810-DLF16250LT5028A1")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/TDK/DLF162500LT-5028A1?qs=U%2FZX79kHR%2FlwIbAISCs3qA%3D%3D")
		(attr "Arrow Part Number" "DLF162500LT-5028A1")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/dlf162500lt-5028a1/tdk?region=nac")
		(attr "Description" "Signal Conditioning LTCC LOW PASS FLTR 2400-2500MHz")
		(attr "Datasheet Link" "https://product.tdk.com/system/files/dam/doc/product/rf/rf/filter/catalog/rf_lpf_dlf162500lt-5028a1_en.pdf")
		(attr "Height" "0.4 mm")
	)

)
