---
title: Donate
layout: template
---
<p>Coming soon</p>
<section class="box">
  <h3>Contact Us by Form</h3>
  <form action="https://formspree.io/your@email.com" method="POST">
  <input type="hidden" name="_next" value="{{ site.url }}{{ site.baseurl }}/thank-you.html" />
  <input type="hidden" name="_subject" value="Stryke Force – Thank you!." />
  <input type="text" name="_gotcha" style="display:none" />
    <div class="row uniform 50%">
      <div class="6u 12u(mobilep)">
        <input type="text" name="name" id="name" value="" placeholder="Name" />
      </div>
      <div class="6u 12u(mobilep)">
        <input type="email" name="_replyto" id="email" value="" placeholder="Email" />
      </div>
    </div>
    <div class="row uniform 50%">
      <div class="12u">
        <textarea name="message" id="message" placeholder="Enter your message" rows="6"></textarea>
      </div>
    </div>
    <div class="row uniform">
      <div class="12u">
        <ul class="actions">
          <li><input type="submit" value="Send Message" /></li>
          <li><input type="reset" value="Reset" class="alt" /></li>
        </ul>
      </div>
    </div>
  </form>
