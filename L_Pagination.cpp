#include "L_Pagination.h"

void L_Pagination::SetCurrentPage(int p_cur_page) {
	collections_page = p_cur_page;
}

void L_Pagination::SetNumPages(int p_num_pages) {
	num_pages = p_num_pages;
}

bool L_Pagination::GoToNext() {
	if (collections_page >= num_pages) {
		return false;
	}
	collections_page++;
	return true;
}

bool L_Pagination::GoToPrevious() {
	if (collections_page <= 1) {
		return false;
	}
	collections_page--;
	return true;
}

int L_Pagination::CurPage() const {
	return collections_page;
}

int L_Pagination::NumPages() const {
	return num_pages;
}

bool L_Pagination::isAtLastPage() {
	return collections_page == num_pages;
}
