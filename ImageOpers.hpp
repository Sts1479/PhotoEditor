/*
 * ImageOpers.hpp
 *
 *  Created on: 4 янв. 2021 г.
 *      Author: user
 */


#ifndef IMAGEOPERS_HPP_
#define IMAGEOPERS_HPP_

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>
#include <utility>

/**
 * \brief класс, который реализует обращение к map
 */
class ImgMap {
private:
	std::map <std::string,cv::Mat> _imgMap;
public:
	ImgMap(){};
	~ImgMap(){};
	void addToMap(const std::string& imgname, const cv::Mat& mat);
	void clearMap ();
	cv::Mat* getMatbyName(const std::string& imgname);
};

/**
 * \brief структура DTO для передачи параметров из Comm в ImageOpers
 */
struct ImgParamsDto {
	std::string pathToFile;
	std::string nameOfImg;
	std::string pathToFileNew;
	std::string nameOfImgNew;
	int newWidth;
	int newHeight;
	int operCode;
	int blurCore;
	void Clear ();
};

/**
 * \brief Основной класс для чтения, обработки и сохранения изображений
 */
class ImageOpers {
public:
	ImageOpers(){};
	~ImageOpers(){};
	ImgMap imgMap;
    void ResizeImage(const std::string& imgname,const std::string& imgname_new, int x, int y);
    void SaveImage(const std::string &imgname, const std::string& imgfile);
    void ImageMain();
    void StoreToMat(const std::string& imgname, const std::string& imgpath);
    void BlurImage(const std::string& imgname, const std::string &imgname_new, int x, int y);// unused method in this realization
    void BlurImage(const std::string& imgname, const std::string &imgname_new, int s);
};


#endif /* IMAGEOPERS_HPP_ */
