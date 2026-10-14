#include <iostream>

struct CameraMetadata {
  int image_id;
  double focal_length_mm;
  double exposure_ms;
};

struct ThermalMetadata {
  int image_id;
  int ambient_temperature;
};

struct SatelliteMetadata {
  int image_id;
  int altitude_km;
  double cloud_coverage;
};

int main() {
  /*
  Здесь реализовано хранение фотографий разных типов: снимки с обычной камеры,
  снимки с тепловизора, снимки со спутника. Изображения могут иметь разные
  размеры, поэтому для эффективного использования памяти каждое изображение
  хранится в отдельном динамическом двумерном массиве. int*** используется для
  хранения массива указателей на эти изображения. Также к каждому снимку
  прилагаются метаданные. Но метаданные разные для разных видов снимков, поэтому
  чтобы их хранить в общем массиве, нужно использовать void*. В этой реализации
  я использую void** - указатель на массив с элементами типа void*. Это мне
  позволяет хранить метаданные разных видов в одном массиве.
  */

  std::cout << "Available types: 1 - camera, 2 - thermal, 3 - satellite\n\n";

  std::cout << "Enter number of images to store: ";
  int n_images;
  std::cin >> n_images;

  int*** images = new int**[n_images];
  int* heights = new int[n_images];
  int* widths = new int[n_images];

  void** metadata = new void*[n_images];
  int* types = new int[n_images];

  for (int n = 0; n < n_images; ++n) {
    int type;
    std::cout << "\nEnter type of image: ";
    std::cin >> type;
    types[n] = type;

    int image_id;
    std::cout << "Enter image id: ";
    std::cin >> image_id;

    if (type == 1) {
      double focal_length_mm;
      std::cout << "Enter focal length (mm): ";
      std::cin >> focal_length_mm;

      double exposure_ms;
      std::cout << "Enter exposure (ms): ";
      std::cin >> exposure_ms;

      CameraMetadata* camera =
          new CameraMetadata{image_id, focal_length_mm, exposure_ms};
      metadata[n] = camera;
    } else if (type == 2) {
      int ambient_temperature;
      std::cout << "Enter ambient temperature: ";
      std::cin >> ambient_temperature;

      ThermalMetadata* thermal =
          new ThermalMetadata{image_id, ambient_temperature};
      metadata[n] = thermal;
    } else if (type == 3) {
      int altitude_km;
      std::cout << "Enter altitude (km): ";
      std::cin >> altitude_km;

      double cloud_coverage;
      std::cout << "Enter cloud coverage: ";
      std::cin >> cloud_coverage;

      SatelliteMetadata* satellite =
          new SatelliteMetadata{image_id, altitude_km, cloud_coverage};
      metadata[n] = satellite;
    }

    int height;
    std::cout << "Enter height of image: ";
    std::cin >> heights[n];

    int width;
    std::cout << "Enter width of image: ";
    std::cin >> width;

    images[n] = new int*[height];
    for (int i = 0; i < height; ++i) {
      images[n][i] = new int[width];
    }
    heights[n] = height;
    widths[n] = width;

    std::cout << "Enter image (" << height << " rows and " << width
              << " cols)\n";
    for (int h = 0; h < height; ++h) {
      for (int w = 0; w < width; ++w) {
        std::cin >> images[n][h][w];
      }
    }

    std::cout << "Image saved\n";
  }

  std::cout << "\nStored images:\n";
  for (int n = 0; n < n_images; ++n) {
    std::cout << "\nImage #" << n + 1 << '\n';

    if (types[n] == 1) {
      CameraMetadata* camera = static_cast<CameraMetadata*>(metadata[n]);
      std::cout << "Type: camera\n"
                << "Image ID: " << camera->image_id << '\n'
                << "Focal length: " << camera->focal_length_mm << " mm\n"
                << "Exposure: " << camera->exposure_ms << " ms\n";
    } else if (types[n] == 2) {
      ThermalMetadata* thermal = static_cast<ThermalMetadata*>(metadata[n]);
      std::cout << "Type: thermal\n"
                << "Image ID: " << thermal->image_id << '\n'
                << "Ambient temperature: " << thermal->ambient_temperature
                << '\n';
    } else if (types[n] == 3) {
      SatelliteMetadata* satellite =
          static_cast<SatelliteMetadata*>(metadata[n]);
      std::cout << "Type: satellite\n"
                << "Image ID: " << satellite->image_id << '\n'
                << "Altitude: " << satellite->altitude_km << " km\n"
                << "Cloud coverage: " << satellite->cloud_coverage << '\n';
    }

    std::cout << "Size: " << heights[n] << " x " << widths[n] << '\n'
              << "Pixels:\n";
    for (int h = 0; h < heights[n]; ++h) {
      for (int w = 0; w < widths[n]; ++w) {
        std::cout << images[n][h][w] << ' ';
      }
      std::cout << '\n';
    }
  }

  for (int i = 0; i < n_images; ++i) {
    for (int j = 0; j < heights[i]; ++j) {
      delete[] images[i][j];
    }

    delete[] images[i];
  }
  delete[] images;

  delete[] heights;
  delete[] widths;

  for (int i = 0; i < n_images; ++i) {
    if (types[i] == 1) {
      delete (CameraMetadata*)metadata[i];
    } else if (types[i] == 2) {
      delete (ThermalMetadata*)metadata[i];
    } else if (types[i] == 3) {
      delete (SatelliteMetadata*)metadata[i];
    }
  }
  delete[] metadata;

  delete[] types;

  return 0;
}
