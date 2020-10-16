import { Component } from "@angular/core";
import { ApiService } from "../services/api.service";

@Component({
  selector: "app-home",
  templateUrl: "home.page.html",
  styleUrls: ["home.page.scss"],
})
export class HomePage {
  constructor(private apiService: ApiService) {}

  sendMessage(message) {
    this.apiService.sendMessage(message);
  }

  disableButton = false;

  disableClick() {
    this.disableButton = true;
  }

  enableClick() {
    this.disableButton = false;
  }
}
