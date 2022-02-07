#include "FileComparison.h"


bool FileComparison::Files_to_cmp(const std::string& file_path1, const std::string& file_path2)
{

	std::ifstream f1(file_path1, std::ios::binary);
	std::ifstream f2(file_path2, std::ios::binary);
	std::ifstream::pos_type size1, size2;

	size1 = f1.seekg(0, std::ifstream::end).tellg();
	f1.seekg(0, std::ifstream::beg);

	size2 = f2.seekg(0, std::ifstream::end).tellg();
	f2.seekg(0, std::ifstream::beg);

	if (size1 != size2)
	{
		f1.close();
		f2.close();
		return false;
	}

	const size_t buffer_size = 4096;
	size_t rmn = size1;

	while (rmn)
	{
		char buffer1[buffer_size], buffer2[buffer_size];
		size_t size = std::min(buffer_size, rmn);

		f1.read(buffer1, size);
		f2.read(buffer2, size);

		if (0 != std::memcmp(buffer1, buffer2, size))
		{
			f1.close();
			f2.close();
			return false;
		}
		rmn -= size;
	}
	f1.close();
	f2.close();
	return true;
}



void FileComparison::Directory_iterator()
{

	list<pair<string, string>> equalfiles;
	fs::path dir1, dir2;
	list<fs::path> filesfrompath1;
	list<fs::path> filesfrompath2;

	cout << "Vvedite katalog 1:";
	cin >> dir1;
	cout << "Vvedite katalog 2:";
	cin >> dir2;
	if (!(fs::exists(dir1) && fs::exists(dir2)))
		cout << "Nepravilno ukazanni directorii, prover'te eshe raz" << endl;
	else {

		for (fs::recursive_directory_iterator it1(dir1), end; it1 != end; ++it1) {
			if (it1->path().extension() == ".txt") {
				filesfrompath1.push_back(*it1);
			}
		}

		for (fs::recursive_directory_iterator it2(dir2), end; it2 != end; ++it2) {
			if (it2->path().extension() == ".txt") {
				filesfrompath2.push_back(*it2);
			}
		}

		for (const auto& p1 : filesfrompath1) {
			for (const auto& p2 : filesfrompath2)
			{
				if (FileComparison::Files_to_cmp(p1.string(), p2.string())) {

					equalfiles.push_back(make_pair(p1.string(), p2.string()));

				}

			}
		}
	}

	if (!equalfiles.empty()) {
		for (const auto& a : equalfiles) {
			cout << a.first << " , " << a.second << " Odinakovie " << endl;
		}
	}
	else { cout << "Odinakovih failov ne naideno" << endl; }
}

