#pragma once

void markInvoicePaidScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	TextInputBox invoiceIDInputBox = { 90, 150, "Invoice ID", true, 10 };
	GUIButton updateInvoiceStatusButton = { 90, 200, "Update Invoice Status" };

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();
		invoiceIDInputBox.update();

		if (updateInvoiceStatusButton.isClicked()) {
			if (invoiceIDInputBox.getInputText().empty()) {
				errorPopup.showMessage("How can we update Status without an ID!\n     Enter an Invoice ID!!");
			}
			else {

				int invoiceID;

				try
				{
					invoiceID = std::stoi(invoiceIDInputBox.getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (!hostelInstance.checkIfInvoiceExists(invoiceID)) {
					errorPopup.showMessage("Invoice Does not Exist!!!\n     Try A different ID!!");
				}
				else if (hostelInstance.checkIfInvoiceIsPaid(invoiceID)) {
					errorPopup.showMessage("Invoice Already Paid!!!");
				}
				else {
					hostelInstance.updateInvoiceStatus(invoiceID, true);
					successPopupMessage = "Invoice Updated Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = MARK_INVOICE_PAID_SCREEN;
				}
			}
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);


		drawCustomBodyText("Update Invoice:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		invoiceIDInputBox.draw();
		updateInvoiceStatusButton.draw();

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}