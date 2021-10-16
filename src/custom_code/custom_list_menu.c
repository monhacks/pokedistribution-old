#ifdef GUARD_CUSTOM_CODE_C

u32 CreateAndPollListMenu(const struct ListMenuItem* items, u8 totalItems, u8 maxShown) {
	s32 response;
	struct ListMenuTemplate listMenuTemplate = custom_sListMenuTemplate_Base;
	struct WindowTemplate windowTemplate = custom_sWindowTemplate_Base;

	listMenuTemplate.items = items;
	listMenuTemplate.totalItems = totalItems;
	listMenuTemplate.maxShowed = maxShown;
	SetListMenuWidth(&listMenuTemplate, &windowTemplate);
	SetListMenuHeight(&listMenuTemplate, &windowTemplate);
	
	response = DoMysteryGiftListMenu(&windowTemplate, &listMenuTemplate, 1, 0x00A, 0xE0);
    if (response != -1)
    {
        ClearWindowTilemap(2);
        CopyWindowToVram(2, COPYWIN_MAP);
    }
    return response;
}

void SetListMenuWidth(struct ListMenuTemplate* listMenuTemplate, struct WindowTemplate* windowTemplate) {
	u32 width;
	s32 finalWidth;
	u32 i;
	
	width = 0;
	for (i = 0; i < listMenuTemplate->totalItems; i++) {
		u32 curWidth = GetStringWidth(2, listMenuTemplate->items[i].label, listMenuTemplate->lettersSpacing);
        if (curWidth > width)
            width = curWidth;
	}
	finalWidth = (((width + 9) / 8) + 2) & ~1;
	windowTemplate->width = finalWidth;
	windowTemplate->tilemapLeft = (30 - finalWidth) / 2;
	return;
}

void SetListMenuHeight(struct ListMenuTemplate* listMenuTemplate, struct WindowTemplate* windowTemplate) {
	u32 height;
	u32 delta;

	height = 0;
	switch (listMenuTemplate->maxShowed) {
		case 2:
			height = 4;
			break;
		case 3:
			height = 6;
			break;
		case 4:
			height = 7;
			break;
		default:
			height = 0;
			break;
	}
	
	windowTemplate->height = height;
	delta = height / 2;
	windowTemplate->tilemapTop = 0x0A - delta - (height % 2);
	return;
}

#endif