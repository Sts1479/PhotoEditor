/*
 * ImageOpers.cpp
 *
 *  Created on: 4 янв. 2021 г.
 *      Author: user
 */
#include "ImageOpers.hpp"
#include "Comm.hpp"
using namespace cv;
using namespace std;
extern ImgParamsDto imgParamsDto;
#include <vector>
/**
 * \brief обнуляем все параметры для методов ImageOpers
 */
void ImgParamsDto::Clear (){
	pathToFile.clear();
	nameOfImg.clear();
	pathToFileNew.clear();
	nameOfImgNew.clear();
	newWidth = 0;
	newHeight = 0;
	operCode = 0;
	blurCore = 0;
}
/**
 *  \brief стирает map
 */
void ImgMap::clearMap (){
	_imgMap.clear();
}

/**
 * \brief помещает в ImgMap матрицу изобр. связанную с именем изобр.
 * \param[in] imgname - имя изображения
 * \param[in] mat - матрица изображения
 */
void ImgMap::addToMap(const std::string& imgname, const cv::Mat& mat){
	    _imgMap[imgname] = mat;
	}
/**
 * \brief ищет и выдает матрицу изобр. по имени
 * \param[in] imgname - имя изображения
 * \return матрица изображения
 */
Mat* ImgMap::getMatbyName(const std::string& imgname){
		auto it = _imgMap.find(imgname);
		if (it == _imgMap.end()){
			std::cout << "The image does not exist, enter correct name of an image." << std::endl;
			return nullptr;
		}
		else {
			return &it->second;
		}
	}
/**
 * \brief сохраняет матрицу изобр., полученную из файла
 * \param[in] imgname - имя изображения
 * \param[in] imgpath - путь к файлу для чтения
 */
void ImageOpers::StoreToMat(const string& imgname, const string& imgpath){
	 Mat img = imread(imgpath, IMREAD_UNCHANGED); // Read in the image file	 auto it = imgMap.find(imgname);
	 if(img.empty()){
		 cout << "Failed to load an image file!" << endl;
		 return;
	 }
	 int rows = img.rows;
	 int cols = img.cols;
	 int channels = img.channels();
     cout << "" << endl;
	 cout << "Image Rows = " << rows << endl;
	 cout << "Image Columns = " << cols << endl;
	 cout << "Image Channels = " << channels << endl;

	 imgMap.addToMap(imgname, img);
	 cout << "Operation successful!" << endl;
}
// unused method in this realization
void ImageOpers::BlurImage(const string& imgname, const string &imgname_new, int x, int y){
	Mat *imgsrc;
	Mat imgdst;
	imgsrc = imgMap.getMatbyName(imgname);
	if (imgsrc == nullptr){
		cout << "The Mat is empty (blur)!" << endl;
		return;
	}
	blur(*imgsrc,imgdst,Size(x,y));
	imgMap.addToMap(imgname_new, imgdst);
	cout << "Operation successful!" << endl;
}
/**
 * \brief сглаживает (фильтрует) изображение
 * \param[in] imgname - имя старого изображения
 * \param[in] imgname_new - имя нового изображения, куда сохр. результат
 * \param[in] s - размер "ядра" сглаживания: если s = N, то ядро будет NxN элементов
 */
void ImageOpers::BlurImage(const string& imgname, const string &imgname_new, int s){
	Mat *imgsrc;
	Mat imgdst;
	imgsrc = imgMap.getMatbyName(imgname);
	if (imgsrc == nullptr){
		cout << "The Mat is empty, incorrect image name (blur)!" << endl;
		return;
	}
	blur(*imgsrc,imgdst,Size(s,s));
	imgMap.addToMap(imgname_new, imgdst);
	cout << "Operation successful!" << endl;
}
/**
 * \brief ресайз изображения
 * \param[in] imgname - имя старого изображения
 * \param[in] imgname_new - имя нового изображения, куда сохр. результат
 * \param[in] x - ширина изображения
 * \param[in] y - высота изображения
 */
void ImageOpers::ResizeImage(const string& imgname, const string& imgname_new, int x, int y){
	Mat *imgsrc;
	Mat imgdst;
	imgsrc = imgMap.getMatbyName(imgname);
	if (imgsrc == nullptr){
		cout << "The Mat is empty, incorrect image name (resize)!" << endl;
		return;
	}
	resize(*imgsrc,imgdst,Size(x,y));
	imgMap.addToMap(imgname_new, imgdst);
	cout << "Operation successful!" << endl;
}
/**
 * \brief сохранение изображения
 * \param[in] imgname - имя изображения
 * \param[in] imgfile - путь к файлу для сохранения
 */
void ImageOpers::SaveImage(const string& imgname, const string& imgfile){
	Mat *img;
	img = imgMap.getMatbyName(imgname);
	if (img == nullptr){
		cout << "The Mat is empty, incorrect image name (save image)!" << endl;
		return;
	}
	int rows = static_cast<int &>(img->rows);
	int cols = static_cast<int &>(img->cols);
	int channels =img->channels();
    cout << "" << endl;
	cout << "Image Rows = " << rows << endl;
	cout << "Image Columns = " << cols << endl;
	cout << "Image Channels = " << channels << endl;
	imwrite(imgfile,*img);
	cout << "Operation successful!" << endl;
}
/**
 * \brief основной метод для операций над изобр.
 */
void ImageOpers::ImageMain(){
	   if (imgParamsDto.operCode == OperCode::LOAD) {
		  imgParamsDto.operCode = OperCode::RESET;
		  StoreToMat(imgParamsDto.nameOfImg, imgParamsDto.pathToFile);
		  imgParamsDto.Clear();
	   }
	   if (imgParamsDto.operCode == OperCode::RESIZE) {
		  imgParamsDto.operCode = OperCode::RESET;
		  ResizeImage(imgParamsDto.nameOfImg,imgParamsDto.nameOfImgNew,imgParamsDto.newWidth,imgParamsDto.newHeight);
		  imgParamsDto.Clear();
	   }
	   if (imgParamsDto.operCode == OperCode::SAVE) {
		  imgParamsDto.operCode = OperCode::RESET;
		  SaveImage(imgParamsDto.nameOfImg,imgParamsDto.pathToFile);
		  imgParamsDto.Clear();
	   }
	   if (imgParamsDto.operCode == OperCode::BLUR) {
		  imgParamsDto.operCode = OperCode::RESET;
		  //BlurImage(imgParamsDto.nameOfImg,imgParamsDto.nameOfImgNew,imgParamsDto.newWidth,imgParamsDto.newHeight);
		  BlurImage(imgParamsDto.nameOfImg,imgParamsDto.nameOfImgNew,imgParamsDto.blurCore);
		  imgParamsDto.Clear();
	   }
}
