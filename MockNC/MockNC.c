#ifdef MNC
#include <stdbool.h>
#include <stdlib.h>
#include "MockNC.h"

MNC_History *first = 0;

bool find_function(void *addr) {
	MNC_History *iterator = first;
	while (iterator) {
		if (iterator->cacheAddress == addr) {
			return true;
		}
		iterator = iterator->next;
	}

	return false;
}

void MNC_Swap_Imp(void *ptr1, void *ptr2) {
	if (!find_function(ptr1)) {
		MNC_History* new_element;
		new_element = (MNC_History*)malloc(sizeof(MNC_History));
		new_element->cacheAddress = ptr1;
		memcpy(&(new_element->cacheValue), ptr1, sizeof(void *));
		new_element->next = first;
		first = new_element;
	}

	memcpy(ptr1, &ptr2, sizeof(void *));
}

void MNC_RESET() {
	MNC_History *iterator = first;
	first = 0;
	while (iterator) {
		memcpy(iterator->cacheAddress, &(iterator->cacheValue), sizeof(void *));
		MNC_History *to_free = iterator;
		iterator = iterator->next;
		free(to_free);
	}
}
#endif