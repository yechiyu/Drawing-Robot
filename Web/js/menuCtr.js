const navLinks = document.querySelectorAll('.nav-link');
const slide = document.querySelector('.slide');


navLinks.forEach((link) => link.addEventListener('click', handleClick));


function handleClick () {
  const index = parseInt(this.dataset.index);
  slide.style.transform = `translateX(${index * 100}%)`;
  navLinks.forEach(link => link.classList.remove('active'));
  this.classList.add('active');
}