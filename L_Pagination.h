#pragma once

class L_Pagination {
public:
	void SetCurrentPage(int p_cur_page);
	void SetNumPages(int p_num_pages);
	bool GoToNext();
	bool GoToPrevious();
	int CurPage() const;
	int NumPages() const;
	bool isAtLastPage();
private:
	int collections_page = 1;
	int num_pages = 1;

};

