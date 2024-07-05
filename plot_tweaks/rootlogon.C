{

	TColor __kOIOrange(TColor::GetFreeColorIndex(), 0.90, 0.60, 0);
	TColor __kOISkyBlue(TColor::GetFreeColorIndex(), 0.35, 0.70, 0.90);
	TColor __kOIBlueGreen(TColor::GetFreeColorIndex(), 0, 0.60, 0.50);
	TColor __kOIYellow(TColor::GetFreeColorIndex(), 0.95, 0.90, 0.25);
	TColor __kOIBlue(TColor::GetFreeColorIndex(), 0, 0.45, 0.70);
	TColor __kOIVermilion(TColor::GetFreeColorIndex(), 0.80, 0.40, 0);
	TColor __kOIRedPurple(TColor::GetFreeColorIndex(), 0.80, 0.60, 0.70);
	Color_t kOkabeItoOrange = __kOIOrange.GetNumber();
	Color_t kOkabeItoSkyBlue = __kOISkyBlue.GetNumber();
	Color_t kOkabeItoBlueGreen = __kOIBlueGreen.GetNumber();
	Color_t kOkabeItoBlue = __kOIBlue.GetNumber();
	Color_t kOkabeItoYellow = __kOIYellow.GetNumber();
	Color_t kOkabeItoVermilion = __kOIVermilion.GetNumber();
	Color_t kOkabeItoRedPurple = __kOIRedPurple.GetNumber();
//	const std::array<Color_t, 8> okabeIto = {kOkabeItoRedPurple, 1, kOkabeItoOrange, kOkabeItoSkyBlue, 
//		kOkabeItoBlueGreen, kOkabeItoYellow, kOkabeItoBlue, kOkabeItoVermilion};
	const std::array<Color_t, 7> okabeIto = {kOkabeItoRedPurple, kOkabeItoOrange, kOkabeItoSkyBlue, 
		kOkabeItoBlueGreen, kOkabeItoYellow, kOkabeItoBlue, kOkabeItoVermilion};

}
