import { Component } from "@angular/core";
import { ApiService } from "../services/api.service";
import { DomSanitizer, SafeResourceUrl, SafeUrl} from '@angular/platform-browser';

@Component({
  selector: "app-home",
  templateUrl: "home.page.html",
  styleUrls: ["home.page.scss"],
})
export class HomePage {
  iframeurl: string;
  larguraIframe: number;
  trustedDashboardUrl : SafeUrl;

  constructor(private apiService: ApiService, private sanitizer: DomSanitizer) {}

  ngOnInit() {
    this.larguraIframe = window.innerWidth - 40;
    this.iframeurl =
      "https://thingspeak.com/channels/1172259/charts/1?width=" +
      this.larguraIframe +
      "&bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=30&type=line&update=15";
    console.log(this.iframeurl)
    
    this.trustedDashboardUrl = this.sanitizer.bypassSecurityTrustResourceUrl(this.iframeurl);
  }
    
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
